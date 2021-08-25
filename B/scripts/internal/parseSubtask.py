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
    for sub in data:
        subtasks.append(data[sub])

    def gidx(a):
        return a["index"]
    subtasks.sort(key=gidx)
    with open(outfile,"w") as f:
        f.write(json.dumps({"subtasks":subtasks}))
        #print(json.dumps({"subtasks":subtasks}))