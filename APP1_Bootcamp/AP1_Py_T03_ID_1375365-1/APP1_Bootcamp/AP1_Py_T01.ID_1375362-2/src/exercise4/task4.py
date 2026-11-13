try:
    N = int(input())

    if N <= 0:
        raise Exception('Natural number was expected')

    triangle = []
    for row in range(N):
        rows = []
        for col in range(row+1):
            if col == 0 or row == col:
                rows.append(1)
            else:
                past_row = triangle[row-1]
                rows.append(past_row[col-1]+past_row[col])
        triangle.append(rows)

    for row in triangle:
        for col in row:
            print(f'{col} ',end='')
        print()

except ValueError:
    print('Natural number was expected')