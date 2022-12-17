import re

with open("day15.input.txt", "r") as f:
    lines = f.readlines()

pattern = re.compile("-?\d+")

ranges = []
row = 2000000
b_on_row = set()

for line in lines:
    numbers = re.findall(pattern, line)
    xs, ys, xb, yb = map(int, numbers)
    dist = abs(xs - xb) + abs(ys - yb)
    ds = abs(row - ys)
    if dist >= ds:
        ranges.append((xs - (dist - ds), xs + (dist - ds)))
    if yb == row:
        b_on_row.add((xb, yb))

cnt = len(b_on_row)

ranges.sort(key=lambda x: x[0])
new_ranges = []
left, right = ranges[0]
for r in ranges[1:]:
    next_left, next_right = r
    if right + 1 < next_left:
        new_ranges.append((left, right))
        left, right = r
    else:
        right = max(right, next_right)
new_ranges.append((left, right))


s = sum(y - x + 1 for x, y in new_ranges)
print(s - cnt)
