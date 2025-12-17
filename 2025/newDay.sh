#!/bin/bash

TEMPLATE="DayX"
YEAR=2025
SESSION_FILE="../.aoc_session"
GITIGNORE="../.gitignore"

# Check template
if [ ! -d "$TEMPLATE" ]; then
  echo "Template folder '$TEMPLATE' not found."
  exit 1
fi

# Ensure session file exists
if [ ! -f "$SESSION_FILE" ]; then
  echo "Advent of Code session file missing."

  touch "$SESSION_FILE"
  chmod 600 "$SESSION_FILE"

  touch "$GITIGNORE"
  if ! grep -qx "/.aoc_session" "$GITIGNORE"; then
    echo "/.aoc_session" >>"$GITIGNORE"
    echo "Added /.aoc_session to ../.gitignore"
  fi

  echo
  echo "Created ../.aoc_session (chmod 600)"
  echo "Paste your AoC session cookie into it, then rerun."
  exit 1
fi

SESSION=$(cat "$SESSION_FILE")

if [ -z "$SESSION" ]; then
  echo "Session file is empty. Paste your AoC token into ../.aoc_session."
  exit 1
fi

# Determine day
if [ -n "$1" ]; then
  DAY_NUM=$(printf "%02d" "$1")
else
  i=1
  while [ -d "Day_$(printf "%02d" "$i")" ]; do
    i=$((i + 1))
  done
  DAY_NUM=$(printf "%02d" "$i")
fi

DAY_INT=$((10#$DAY_NUM))
NEW_DIR="Day_$DAY_NUM"

cp -r "$TEMPLATE" "$NEW_DIR"
echo "Created $NEW_DIR"

BASE_URL="https://adventofcode.com/$YEAR/day/$DAY_INT"

# Fetch problem HTML
HTML=$(curl -s "$BASE_URL")

# Save Markdown formatted problem description
echo "$HTML" |
  sed -n '/<article class="day-desc">/,/<\/article>/p' |
  sed 's/<article class="day-desc">/# Day '"$DAY_INT"'\n/' |
  sed 's/<h2>/## /g; s/<\/h2>//g' |
  sed 's/<p>/\n/g; s/<\/p>/\n/g' |
  sed 's/<pre><code>/```\n/g; s/<\/code><\/pre>/\n```\n/g' |
  sed 's/<[^>]*>//g' \
    >"$NEW_DIR/Problem_Description.md"

echo "Saved Problem_Description.md"

# Extract example input (first code block only)
echo "$HTML" |
  sed -n '/<pre><code>/,/<\/code><\/pre>/p' |
  sed 's/<pre><code>//; s/<\/code><\/pre>//' |
  sed 's/&lt;/</g; s/&gt;/>/g; s/&amp;/\&/g' \
    >"$NEW_DIR/example_input.txt"

echo "Extracted example_input.txt"

# Fetch real puzzle input
curl -s \
  -H "Cookie: session=$SESSION" \
  "$BASE_URL/input" \
  >"$NEW_DIR/puzzle_input.txt"

echo "Saved puzzle_input.txt"
echo "Day $DAY_NUM ready."

nvim -c "cd $NEW_DIR" "$NEW_DIR/main.cpp"
