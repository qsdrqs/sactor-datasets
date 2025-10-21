from format_failure_info import is_translated
import os, json

dirs_gpt5 = [
    r"/home/zhang/code/sactor/experiment/ogg/ogg/sactor_result_bitwise-gpt5/",
    r"/home/zhang/code/sactor/experiment/ogg/ogg/sactor_result_framing-gpt5/"]
dirs_gpt4o = [
    r"/home/zhang/code/sactor/experiment/ogg/ogg/sactor_result_bitwise-gpt4o/",
    r"/home/zhang/code/sactor/experiment/ogg/ogg/sactor_result_framing-gpt4o/"]
   

def summarize_one_file(src_path, src_dir) -> list:
    res = {}
    with open(src_path) as f:
        src = json.load(f)    
        for name, status in src.items():
            if status['type'] != 'function':
                continue
            if status['status'] != 'success':
                continue
            if (status['status'] == 'success' and is_translated(name, 'function', src_dir) != True) or \
                status['status'] != 'success' and is_translated(name, 'function', src_dir):
                print(f"Warning: function `{name}` failure info status is inconsistent with translation files. failure_info: {src_path}")
            
            attempts = status['attempts']
            res[name] = sum(attempts)
    return res

def get_function_and_attempts(dirs):
    category = "idiomatic"
    result = {}
    for directory in dirs:
        src_dir = os.path.join(directory, f"translated_code_{category}")
        src_path = os.path.join(directory, f"{category}_failure_info.json")
        result.update(summarize_one_file(src_path, src_dir))
    return result

def print_attempts(dirs_gpt4o, dirs_gpt5):
    res4o = get_function_and_attempts(dirs_gpt4o)
    res5 = get_function_and_attempts(dirs_gpt5)
    common_keys = res4o.keys() & res5.keys()
    print("functions that gpt4o has but gpt5 result does not have:", str(res4o.keys() - common_keys))
    print("functions that gpt5 has but gpt4o result does not have:", str(res5.keys() - common_keys))
    res4o_common = {key: res4o[key] for key in common_keys}
    res5_common = {key: res5[key] for key in common_keys}
    print("average gpt4o:", sum(res4o_common.values()) / len(res4o_common))
    print("average gpt5:", sum(res5_common.values()) / len(res4o_common))



if __name__ == "__main__":
    print_attempts(dirs_gpt4o, dirs_gpt5)

