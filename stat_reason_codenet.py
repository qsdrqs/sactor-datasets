import json
import os
from collections import defaultdict, Counter

# Define the categories and their corresponding issue descriptions
category_mapping = {
  "R1. Improper translation of command-line argument handling or try to fix wrong command-line argument handling": [
    "Mishandling of argv parameters in the main function's translation leading to incorrect argument indexing",
    "The generated Rust code does not properly handle command-line arguments, leading to incorrect parsing of program inputs and parameters"
  ],

  "R2. Function naming mismatches between C and Rust": [
    "Incorrect translation of function names' casing conventions, causing function signature mismatches",
    "Duplication of function definitions during code generation leading to multiple identical function entries",
    "The tool's translation of character array accesses in C generates incorrect pointer dereferences in Rust, leading to attempts to dereference byte values (i8) as pointers"
  ],

  "R3. Format string directive mistranslation causing output inconsistencies": [
    "Format string translation error causing literal character differences in output",
    "The generated Rust code does not handle empty input strings, leading to index out-of-bounds panics when accessing the first character",
    "The generated Rust code computes the string length using the entire buffer size instead of stopping at the null terminator like C's strlen"
  ],

  "R4. Random number generation seed value handling discrepancies": [
    "Incorrect seed value handling due to signed/unsigned casting differences between C's implicit conversions and Rust's explicit casts",
    "Incorrect type conversion when handling the seed value for srand, leading to different random number sequences between C and Rust"
  ],

  "R5. \\sys{} unable to translate mutable global state variables": [
    "Incorrect handling of mutable global variables between C and Rust semantics",
    "The generated Rust code uses C's `min` and `max` functions via `libc` or other unsafe implementations, requiring unsafe blocks, instead of Rust's safe `std::cmp::min` and `std::cmp::max`"
  ],

  "R6. Mismatched data type translations": [
    "Incorrect memory management of CString pointers leading to invalid frees of stack-allocated buffers",
    "Incorrect handling of C standard library types and functions (e.g., c_char, size_t, stderr) when translating to Rust's libc crate and FFI bindings",
    "The generated Rust code uses i32 for array indices and arithmetic operations where usize is required, leading to type mismatches and potential underflow when casting negative values to usize",
    "The generated Rust code uses i32 for variables that were declared as long long int in the C code, causing arithmetic overflow in sum operations",
    "The generated Rust code attempts to create fixed-size arrays using dynamically determined sizes (from function parameters), leading to a compile error"
  ],

  "R7. Incorrect control flow or loop boundary condition translations": [
    "Incorrect handling of loop termination conditions that leads to off-by-one errors in index calculations between C and Rust",
    "The generated Rust code incorrectly maps C's memset operation on a contiguous 2D array to a non-contiguous Vec<Vec<T>> structure in Rust",
    "The generated Rust code does not handle the case where left-shifting 1 by 'n' bits exceeds the integer type's bit width, causing overflow panics",
    "The generated Rust code lacks bounds checking for the input parameter 'm' being within the valid range of the allocated array"
  ]
}
# Create a reverse mapping from issue descriptions to categories
issue_to_category = {}
for category, issues in category_mapping.items():
    for issue in issues:
        issue_to_category[issue] = category

def count_categories(json_files):
    # Initialize counters
    category_counts = Counter()
    issue_counts = Counter()
    file_counts = defaultdict(set)  # To track unique C files per category

    # Process each JSON file
    for json_file in json_files:
        try:
            with open(json_file, 'r') as f:
                data = json.load(f)

            # Count issues and their categories
            for issue, files in data.items():
                category = issue_to_category.get(issue, "Uncategorized")

                # Count each instance of the issue
                issue_counts[issue] += len(files)

                # Count category (each file counts once per category)
                for file in files:
                    file_counts[category].add(file)

        except (json.JSONDecodeError, FileNotFoundError) as e:
            print(f"Error processing {json_file}: {e}")

    # Calculate category counts from unique files
    for category, files in file_counts.items():
        category_counts[category] = len(files)

    return category_counts, issue_counts, file_counts

def print_results(category_counts, issue_counts, file_counts):
    print("\n===== CATEGORY COUNTS =====")
    total_files = set()
    for category, count in sorted(category_counts.items()):
        print(f"{category.split('.')[0]}: {count} files")
        total_files.update(file_counts[category])

    # print(f"\nTotal unique files across all categories: {len(total_files)}")
    #
    # print("\n===== ISSUE COUNTS =====")
    # for issue, count in sorted(issue_counts.items(), key=lambda x: x[1], reverse=True):
    #     category = issue_to_category.get(issue, "Uncategorized")
    #     print(f"{category} - {count} occurrences:")
    #     print(f"  {issue[:100]}..." if len(issue) > 100 else f"  {issue}")
    #     print()

if __name__ == "__main__":
    # You can specify the path to your JSON files here
    import sys
    json_files = [
        sys.argv[1]
    ]

    # Or you can use this to automatically find all JSON files in the current directory
    # json_files = [f for f in os.listdir() if f.endswith('.json')]

    print(f"Processing {len(json_files)} JSON files...")
    category_counts, issue_counts, file_counts = count_categories(json_files)
    print_results(category_counts, issue_counts, file_counts)
