from functools import cmp_to_key

# True if in order
# False if not
# None if equal


def compare(a: int | list, b: int | list) -> bool | None:
    if isinstance(a, list) and isinstance(b, list):
        for i in range(min(len(a), len(b))):
            if compare(a[i], b[i]) is True:
                return True
            elif compare(a[i], b[i]) is False:
                return False

        if len(a) < len(b):
            return True
        elif len(a) > len(b):
            return False

    elif isinstance(a, int) and isinstance(b, int):
        if a > b:
            return False
        elif a < b:
            return True
    elif isinstance(a, int) and isinstance(b, list):
        if compare([a], b) is True:
            return True
        if compare([a], b) is False:
            return False
    elif isinstance(a, list) and isinstance(b, int):
        if compare(a, [b]) is True:
            return True
        if compare(a, [b]) is False:
            return False\



def sortCmp(li: list) -> list:
    for i in range(len(li) - 1):
        for j in range(i + 1, len(li)):
            if not compare(li[i], li[j]):
                li[i], li[j] = li[j], li[i]
    return li


with open("day13.input.txt", "r") as f:
    lines = list(map(lambda x: eval(x.strip()), filter(
        lambda l: not l.isspace(), f.readlines())))

s = 0

for i in range(0, len(lines), 2):
    first = lines[i]
    second = lines[i + 1]

    if compare(first, second):
        s += (i // 2 + 1)
# Part 1
print(s)

# Part 2
lines += [[[2]], [[6]]]
lines = sortCmp(lines)

f = s = 0

for i, e in enumerate(lines):
    if e == [[2]]:
        f = i + 1
    elif e == [[6]]:
        s = i + 1

print(f * s)
