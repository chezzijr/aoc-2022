# Part 1 function
def find_possible_pos(board: list[list[str]], y: int, x: int, max_y: int):
    obs = {'#', 'o'}
    while y != max_y - 1:
        if board[y + 1][x] not in obs:
            y += 1
        elif board[y + 1][x - 1] not in obs:
            y += 1
            x -= 1
        elif board[y + 1][x + 1] not in obs:
            y += 1
            x += 1
        else:
            return (y, x)
    return None


# Part 2 function (I don't know how to name)
def simulate(obs: set[tuple[int, int]], y: int, x: int, max_y: int):
    while y != max_y - 1:
        if (y + 1, x) not in obs:
            y += 1
        elif (y + 1, x - 1) not in obs:
            y += 1
            x -= 1
        elif (y + 1, x + 1) not in obs:
            y += 1
            x += 1
        else:
            return (y, x)
    return (max_y - 1, x)


with open("day14.input.txt", "r") as f:
    lines = f.readlines()

rock_structures = len(lines)

# Get rid of end line character
# Type: iterator of strings
lines = map(lambda l: l.strip(), lines)

# Split each lines into final coordinates string
# Type: iterator of lists of strings
lines = map(lambda l: l.split(" -> "), lines)

# Convert each coordinates to tuple of 2 coordinates
# Type: iterator of tuple of coordinates
structs = []
x_max = y_max = 0
x_min = float('inf')
for line in lines:
    struct = []
    for s in line:
        x, y = map(int, s.split(','))
        x_max = max(x_max, x)
        y_max = max(y_max, y)
        x_min = min(x_min, x)
        struct.append((x, y))
    structs.append(struct)

# Padding
x_min -= 1
x_max += 2
y_max += 2

# PART 1
# I use array for visualization
scans = [['.' for _ in range(x_min, x_max)] for _ in range(y_max)]
for struct in structs:
    for i in range(1, len(struct)):
        x_from, y_from = struct[i - 1]
        x_to, y_to = struct[i]
        x_it = range(x_from, x_to + 1) \
            if x_to >= x_from else range(x_from, x_to - 1, -1)
        y_it = range(y_from, y_to + 1) \
            if y_to >= y_from else range(y_from, y_to - 1, -1)
        for y in y_it:
            for x in x_it:
                scans[y][x - x_min] = '#'
count = 0
while True:
    pos = find_possible_pos(scans, 0, 500 - x_min, y_max)
    if not pos:
        break
    else:
        y, x = pos
        scans[y][x] = 'o'
        count += 1

print(count)

# PART 2
# use set to store the obstacles

obs = set()
for struct in structs:
    for i in range(1, len(struct)):
        x_from, y_from = struct[i - 1]
        x_to, y_to = struct[i]
        x_it = range(x_from, x_to + 1) \
            if x_to >= x_from else range(x_from, x_to - 1, -1)
        y_it = range(y_from, y_to + 1) \
            if y_to >= y_from else range(y_from, y_to - 1, -1)
        for y in y_it:
            for x in x_it:
                obs.add((y, x))

cnt = 0
while True:
    if (0, 500) in obs:
        break
    pos = simulate(obs, 0, 500, y_max)
    obs.add(pos)
    cnt += 1

print(cnt)
