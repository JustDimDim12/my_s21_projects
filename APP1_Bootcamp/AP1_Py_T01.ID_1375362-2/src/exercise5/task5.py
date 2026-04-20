try:
    def make_num(a):
        num = list(a)
        res = 0
        el = 0
        negate = 1
        if num[0] == '-':
            negate = -1
            num = num[1:]
        elif num[0] == '+':
            num = num[1:]
        is_float = False
        if '.' not in a:
            count_int = len(num) - 1
        else:
            count_int = len(num[:num.index('.')]) - 1
        count_float = 1
        for i in range(len(num)):
            if num[i] == '.':
                is_float = True
                continue
            el = num_dict[num[i]]
            if not is_float:
                res += el * 10**count_int
                count_int -= 1
            else:
                res += el / 10**count_float
                count_float += 1
        return res * negate


    num_dict = {
        '0': 0,
        '1': 1,
        '2': 2,
        '3': 3,
        '4': 4,
        '5': 5,
        '6': 6,
        '7': 7,
        '8': 8,
        '9': 9
    }

    s = input().strip()
    valid_chars = set('0123456789+-.')
    if not s:
        raise Exception("Wrong input!")
    if not any(c in valid_chars for c in s):
        raise Exception("Wrong input!")

    print(f'{make_num(s)*2:.3f}', sep='')
except:
    print("Wrong input!")