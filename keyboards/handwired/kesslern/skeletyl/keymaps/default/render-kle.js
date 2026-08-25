#!/usr/bin/env node
// Renders a raw keyboard-layout-editor.com JSON file to an SVG (and optionally PNG).
// Usage: node render-kle.js <input.json> <output.svg>

const fs = require("fs");
const path = require("path");
// Vendored verbatim from https://www.keyboard-layout-editor.com/serial.js
// (the exact parser the live site uses) -- the published @ijprest/kle-serial
// npm package (0.15.1) resolves rotated-row x/y differently and mis-places
// any key whose row sets r/rx/ry, so we deliberately don't use it.
const serial = require(path.join(__dirname, "kle-serial.js"));

const [, , inPath, outPath] = process.argv;
if (!inPath || !outPath) {
  console.error("Usage: node render-kle.js <input.json> <output.svg>");
  process.exit(1);
}

const UNIT = 54; // px per keyboard unit, matches KLE's default on-screen scale
const PAD = 3; // gap between adjacent keycaps

const raw = fs.readFileSync(inPath, "utf8");
const rows = JSON.parse(raw);
const { meta, keys } = serial.deserialize(rows);
const keyboard = { meta, keys };

function esc(s) {
  return String(s)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

// Label grid positions (KLE reading order, 0-11): row major, 3 cols x 4 rows
// col: 0=left,1=center,2=right  row: 0=top,1=center-top,2=center-bottom,3=bottom
const ANCHOR = ["start", "middle", "end"];
const COL_FRAC = [0.08, 0.5, 0.92];
const ROW_FRAC = [0.22, 0.42, 0.62, 0.86];

let minX = 0, minY = 0, maxX = 0, maxY = 0;
for (const k of keyboard.keys) {
  const pts = keyRectCorners(k);
  for (const [x, y] of pts) {
    minX = Math.min(minX, x);
    minY = Math.min(minY, y);
    maxX = Math.max(maxX, x);
    maxY = Math.max(maxY, y);
  }
}

function keyRectCorners(k) {
  const rects = [[k.x, k.y, k.width, k.height]];
  if (k.width2 || k.height2) {
    rects.push([k.x + k.x2, k.y + k.y2, k.width2 || k.width, k.height2 || k.height]);
  }
  const corners = [];
  for (const [x, y, w, h] of rects) {
    for (const [cx, cy] of [[x, y], [x + w, y], [x, y + h], [x + w, y + h]]) {
      corners.push(rotatePoint(cx, cy, k));
    }
  }
  return corners;
}

function rotatePoint(x, y, k) {
  if (!k.rotation_angle) return [x, y];
  const rad = (k.rotation_angle * Math.PI) / 180;
  const ox = k.rotation_x, oy = k.rotation_y;
  const dx = x - ox, dy = y - oy;
  return [ox + dx * Math.cos(rad) - dy * Math.sin(rad), oy + dx * Math.sin(rad) + dy * Math.cos(rad)];
}

const marginU = 0.5;
minX -= marginU; minY -= marginU; maxX += marginU; maxY += marginU;

const widthPx = (maxX - minX) * UNIT;
const heightPx = (maxY - minY) * UNIT;

let svg = `<svg xmlns="http://www.w3.org/2000/svg" width="${widthPx.toFixed(0)}" height="${heightPx.toFixed(0)}" viewBox="0 0 ${widthPx.toFixed(0)} ${heightPx.toFixed(0)}" font-family="Helvetica, Arial, sans-serif">\n`;
svg += `<rect x="0" y="0" width="${widthPx.toFixed(0)}" height="${heightPx.toFixed(0)}" fill="${keyboard.meta.backcolor || "#eeeeee"}"/>\n`;

for (const k of keyboard.keys) {
  const gx = (k.x - minX) * UNIT;
  const gy = (k.y - minY) * UNIT;
  const w = k.width * UNIT;
  const h = k.height * UNIT;
  const rotX = (k.rotation_x - minX) * UNIT;
  const rotY = (k.rotation_y - minY) * UNIT;
  const transform = k.rotation_angle
    ? `transform="rotate(${k.rotation_angle} ${rotX.toFixed(2)} ${rotY.toFixed(2)})"`
    : "";

  svg += `<g ${transform}>\n`;

  if (!k.decal && !k.ghost) {
    const fill = k.color || "#f5f5f5";
    svg += `  <rect x="${(gx + PAD).toFixed(2)}" y="${(gy + PAD).toFixed(2)}" width="${(w - PAD * 2).toFixed(2)}" height="${(h - PAD * 2).toFixed(2)}" rx="5" ry="5" fill="${fill}" stroke="#888888" stroke-width="1"/>\n`;
    if (k.width2 || k.height2) {
      const gx2 = gx + k.x2 * UNIT;
      const gy2 = gy + k.y2 * UNIT;
      const w2 = (k.width2 || k.width) * UNIT;
      const h2 = (k.height2 || k.height) * UNIT;
      svg += `  <rect x="${(gx2 + PAD).toFixed(2)}" y="${(gy2 + PAD).toFixed(2)}" width="${(w2 - PAD * 2).toFixed(2)}" height="${(h2 - PAD * 2).toFixed(2)}" rx="5" ry="5" fill="${fill}" stroke="#888888" stroke-width="1"/>\n`;
    }
  }

  if (!k.ghost) {
    for (let i = 0; i < (k.labels || []).length; i++) {
      const label = k.labels[i];
      if (!label) continue;
      const row = Math.floor(i / 3);
      const col = i % 3;
      const lx = gx + w * COL_FRAC[col];
      const ly = gy + h * ROW_FRAC[row];
      const size = k.textSize[i] || k.default.textSize || 3;
      const fontPx = 6 + 2 * size;
      const color = k.textColor[i] || k.default.textColor || "#000000";
      const text = esc(label.replace(/<br\/?>/gi, " / ").replace(/<[^>]+>/g, ""));
      svg += `  <text x="${lx.toFixed(2)}" y="${ly.toFixed(2)}" font-size="${fontPx}" fill="${color}" text-anchor="${ANCHOR[col]}" dominant-baseline="middle">${text}</text>\n`;
    }
  }

  svg += `</g>\n`;
}

svg += `</svg>\n`;
fs.writeFileSync(outPath, svg);
console.error(`Wrote ${outPath} (${keyboard.keys.length} keys)`);
