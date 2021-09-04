import subprocess
import json
import os

BASE_DIR = os.environ.get('BASE_DIR')

SOLUTIONS_JSON = os.environ.get('SOLUTIONS_JSON')


def load_data(json_file):
    try:
        with open(json_file, 'r') as f:
            try:
                data = json.load(f)
            except ValueError:
                print('invalid json')
                return None
    except IOError:
        print('file does not exist')
        return None
    return data


def run_solutions():
    solutions = load_data(SOLUTIONS_JSON)

    for solution in solutions:
        print(solution)
        subprocess.run([
            'tps', 'invoke', os.path.join('solution', solution)
        ])
        print()


if __name__ == "__main__":
    run_solutions()
