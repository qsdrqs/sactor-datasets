import json, os

RESULT_DIR = r"/home/zhang/code/sactor/experiment/ogg/ogg/sactor_result_bitwise-gpt4o/"

def is_translated(name: str, ty: str, src_dir: str) -> bool:
    path = os.path.join(src_dir,  f"{ty}s", f"{name}.rs")
    if os.path.isfile(path):
        return True
    return False

def format_failure_info(name: str, info: dict) -> list:
    out = []
    out.append("===========================================================\n")
    out.append(f"--------------------------\nfunction name: {name}\n\n")
    if info["errors"]:
        error = info["errors"][-1]
        out.append(f"--------------------------\nerror type: {error['type']}\n\n")
        out.append(f"--------------------------\ntranslation:\n{error['translation']}\n\n")
        out.append(f"--------------------------\nmessage:\n{error['message']}\n\n\n")
    else:
        out.append("Not translated\n")
    return out


if __name__ == "__main__":
    categories = ["idiomatic", "unidiomatic"]
    for category in categories:
        src_dir = os.path.join(RESULT_DIR, f"translated_code_{category}")
        src_path = os.path.join(RESULT_DIR, f"{category}_failure_info.json")
        out_path = os.path.join(src_dir, "formated_failure_info.txt") 

        with open(src_path) as f:
            infos = json.load(f)

        with open(out_path, 'w') as f:
            for name, info in infos.items():
                if info['type'] == 'function' and not is_translated(name, "function", src_dir):
                    out = format_failure_info(name, info)
                    f.writelines(out)

