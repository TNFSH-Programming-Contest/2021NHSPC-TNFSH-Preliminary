import json
import sys
from functools import cmp_to_key

if __name__ == '__main__':
    inpfile = sys.argv[1]
    outfile = sys.argv[2]
    with open(inpfile) as f:
        data = json.loads(f.read())
        data = data["subtasks"]
    subtasks = []
    offset = 1 if 'samples' in data else 0
    for sub in data:
        data[sub]['index'] += offset
        subtasks.append(data[sub])

    def gidx(a):
        return a["index"]
    subtasks.sort(key=gidx)
    with open(outfile, "w") as f:
        f.write(json.dumps({"subtasks": subtasks}))
