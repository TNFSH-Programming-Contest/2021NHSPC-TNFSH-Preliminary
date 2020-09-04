#!/bin/bash
CONTEST_NAME="$(${PYTHON} "${INTERNALS}/json_extract.py" "${PROBLEM_JSON}" "contest_name")"
PROBLEM_LABEL="$(${PYTHON} "${INTERNALS}/json_extract.py" "${PROBLEM_JSON}" "problem_label")"
PROBLEM_NAME="$(${PYTHON} "${INTERNALS}/json_extract.py" "${PROBLEM_JSON}" "title")"
PROBLEM_ID="$(${PYTHON} "${INTERNALS}/json_extract.py" "${PROBLEM_JSON}" "name")"
${PYTHON} "${INTERNALS}/parseSubtask.py" "${BASE_DIR}/subtasks.json" "${BASE_DIR}/subtask-pandoc.json"

echo "Compiling ${CONTEST_NAME} - ${PROBLEM_LABEL}. ${PROBLEM_NAME} (${PROBLEM_ID})"

pandoc --metadata-file="${BASE_DIR}/subtask-pandoc.json" --metadata-file="${BASE_DIR}/problem.json" -T "" ${STATEMENT_DIR}/index.md -o ${STATEMENT_DIR}/index.pdf --template ${BASE_DIR}/../template.tex --resource-path ${STATEMENT_DIR} -f markdown -t latex -s --pdf-engine=xelatex

echo "Compile Finish"
rm "${BASE_DIR}/subtask-pandoc.json"
