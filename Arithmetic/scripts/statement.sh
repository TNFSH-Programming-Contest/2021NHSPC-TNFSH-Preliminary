CONTEST_NAME="$(python "${INTERNALS}/json_extract.py" "${PROBLEM_JSON}" "contest_name")"
PROBLEM_LABEL="$(python "${INTERNALS}/json_extract.py" "${PROBLEM_JSON}" "problem_label")"
PROBLEM_NAME="$(python "${INTERNALS}/json_extract.py" "${PROBLEM_JSON}" "title")"
PROBLEM_ID="$(python "${INTERNALS}/json_extract.py" "${PROBLEM_JSON}" "name")"

echo "Compiling ${CONTEST_NAME} - ${PROBLEM_LABEL}. ${PROBLEM_NAME} (${PROBLEM_ID})"

pandoc -M contestName="${CONTEST_NAME}" -M problemLabel="${PROBLEM_LABEL}" -M problemName="${PROBLEM_NAME}" -M problemId="${PROBLEM_ID}" -T "" ${STATEMENT_DIR}/index.md -o ${STATEMENT_DIR}/index.pdf --template ${BASE_DIR}/../template.tex --resource-path ${STATEMENT_DIR} -f markdown -t latex -s --pdf-engine=xelatex

echo "Compile Finish"
