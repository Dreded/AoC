#!/bin/bash

SESSION_FILE="../../.aoc_session"

# Ensure session file exists
if [ ! -f "$SESSION_FILE" ]; then
  echo "ERROR: Session file missing: $SESSION_FILE"
  echo "Please create it and paste your AoC session token inside."
  exit 1
fi

# Read session
AOC_SESSION=$(cat "$SESSION_FILE")

# Determine year and day from current working directory
DAY_NUM=$(basename "$PWD" | sed 's/Day_//')
YEAR=$(basename "$(dirname "$PWD")")
DAY_INT=$((10#$DAY_NUM))
BASE_URL="https://adventofcode.com/$YEAR/day/$DAY_INT"

# Fetch HTML
HTML=$(curl -s -H "Cookie: session=$AOC_SESSION" "$BASE_URL")

# Check if session is invalid
if echo "$HTML" | grep -q '/auth/github'; then
  echo "ERROR: Session token expired or invalid."
  exit 1
fi

# Extract Part Two description
echo "$HTML" |
  sed -n '/<h2 id="part2">/,/<\/article>/p' |         # from Part Two header to end of article
  sed -e 's/<h2 id="part2">.*<\/h2>/## Part Two\n/' | # replace header with markdown
  sed 's/<[^>]*>//g' >Part2_Description.md            # strip remaining HTML tags

echo "Saved Part2_Description.md"
