import os, json

filename = input()

if os.path.getsize(filename) == 0:
    raise Exception('Empty file')
try:
    file = open(filename,'r')
    data = json.load(file)
    file.close()

    merged_data = data["list1"] + data["list2"]
    res = sorted(merged_data, key = lambda element: element["year"])
    print(json.dumps(res, indent=2, ensure_ascii=False))
except:
    print('Error')