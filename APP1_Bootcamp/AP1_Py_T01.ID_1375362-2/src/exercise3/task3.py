def coordinates_checker(matrix, was_here):
    figure = set()
    temp = [(i, j)]

    while temp:
        x, y = temp.pop(0)
        figure.add((x, y))

        for x1, y1 in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            x2, y2 = x + x1, y + y1
            if 0 <= x2 < rows and 0 <= y2 < cols:
                if matrix[x2][y2] == 1 and not was_here[x2][y2]:
                    was_here[x2][y2] = 1
                    temp.append((x2, y2))
    return figure

def figure_type(figure):
    res = ''
    x_figure = [i[0] for i in figure]
    y_figure = [i[1] for i in figure]

    width = max(x_figure) - min(x_figure) + 1
    height = max(y_figure) - min(y_figure) + 1
    exp_size = width * height
    if width == height and exp_size == len(figure):
        res = 'square'
    else:
        res = 'circle'
    return res

file = open('input.txt', 'r')
f = file.readlines()
matrix = [list(map(int, line.split())) for line in f]

squares = circles = 0
rows, cols = len(matrix), len(matrix[0])
was_here = []

for i in range(rows):
    was_here.append([])
    for j in range(cols):
        was_here[i].append(0)

for i in range(rows):
    for j in range(cols):
        if matrix[i][j] == 1 and was_here[i][j] == 0:
            figure = coordinates_checker(matrix, was_here)

            if figure_type(figure) == 'square':
                squares += 1
            elif figure_type(figure) == 'circle':
                circles += 1

print(squares, circles)