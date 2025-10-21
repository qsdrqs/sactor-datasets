from format_failure_info import is_translated
import openpyxl
import os, json

RESULT_DIR = r"/home/zhang/code/sactor/experiment/ogg/ogg/sactor_result_bitwise/"

def summarize_one_category(src_path, src_dir) -> list:
    """
    name, failed?, failure cause, failure summary, failure detail, translation, num of attempts, attempts for each run
    """
    with open(src_path) as f:
        src = json.load(f)
    successes = []
    failures = []
    for name, status in src.items():
        if status['type'] != 'function':
            continue
        if (status['status'] == 'success' and is_translated(name, 'function', src_dir) != True) or \
            status['status'] != 'success' and is_translated(name, 'function', src_dir):
            print(f"Warning: function `{name}` failure info status is inconsistent with translation files. failure_info: {src_path}")
        
        attempts = status['attempts']
        if status['status'] == 'success':
            successes.append(
                (
                    name,
                    0,
                    "",
                    "",
                    "",
                    "",
                    sum(attempts),
                    str(attempts)
                )
            )
        else:
            error = status['errors'][-1]
            cause = error['type']
            if error['message'].startswith("Error: Failed to get compilable test harness for"):
                cause = "TEST_HARNESS_COMPILE_ERROR"
            failures.append(
                (
                    name, 
                    1,
                    cause,
                    "",
                    error['message'].strip(),
                    error['translation'].strip(),
                    sum(attempts),
                    str(attempts)
                )
            )
    failures.extend(successes)
    return failures

def produce_summary_file():
    categories = ["unidiomatic", "idiomatic"]
    out_path = os.path.join(RESULT_DIR, "summary_failure_info.xlsx") 
    output = []
    for category in categories:
        src_dir = os.path.join(RESULT_DIR, f"translated_code_{category}")
        src_path = os.path.join(RESULT_DIR, f"{category}_failure_info.json")
        output.append((category,))
        output.append(('name', 'failed?', 'failure cause', 'failure summary', 'failure detail', 'translation', 'num of attempts', 'attempts for each run'))
        res = summarize_one_category(src_path, src_dir)
        output.extend(res)
        output.append(("",))
        output.append(("",))
    wb = openpyxl.Workbook()
    sheet = wb.active
    for line in output:
        sheet.append(line)
    wb.save(out_path)


if __name__ == "__main__":
    produce_summary_file()

