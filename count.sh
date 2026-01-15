#!/usr/bin/env bash

# setting root as a first argument or "." as default
ROOT_DIR="${1:-.}"

# excluding directories
EXCLUDE_DIRS=(
  ".git"
  "build"
  "html"
  "latex"
)

EXCLUDE_ARGS=()
for dir in "${EXCLUDE_DIRS[@]}"; do
  EXCLUDE_ARGS+=(-path "*/$dir/*" -prune -o)
done


# counting files and lines of code
TOTAL_LINES=0
TOTAL_FILES=0

while IFS= read -r -d '' file; do
  TOTAL_FILES=$((TOTAL_FILES + 1))

  # Check extension for line counting
  case "${file##*.}" in
    (c|h|cpp|hpp)
      lines=$(wc -l < "$file")
      TOTAL_LINES=$((TOTAL_LINES + lines))
      ;;
  esac

done < <(
  find "$ROOT_DIR" \
    "${EXCLUDE_ARGS[@]}" \
    -type f -print0
)

echo "Directory: $ROOT_DIR"
echo "Excluded directories: ${EXCLUDE_DIRS[*]}"
echo "----------------------------------------"
echo "Total files (all types): $TOTAL_FILES"
echo "Total lines (c/h/cpp/hpp only): $TOTAL_LINES"