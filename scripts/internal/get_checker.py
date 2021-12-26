import sys
import os

from util import simple_usage_message, load_json, log_warning
from json_extract import navigate_json
import tests_util as tu


SUBTASKS_JSON = os.environ.get('SUBTASKS_JSON')


def get_checker():
    data = load_json(SUBTASKS_JSON)

    global_checker = data.get('global_checker', [])

    return global_checker


if __name__ == '__main__':
    for checker in get_checker():
        print(checker)
