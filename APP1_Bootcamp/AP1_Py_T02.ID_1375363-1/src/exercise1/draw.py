from questions import Question
from students import Student
from examiners import Examiner
import time
import sys

last_nrows = None

def draw_change(table): #изменение отображения таблиц
    global last_nrows

    csi_up = f"\x1B[{last_nrows}A"
    csi_clr = "\x1B[0K"
    n = len(table)
    out = ["\x1B[?25l"]
    if last_nrows: out.append(csi_up)
    out += [f"\r{line}{csi_clr}\n" for line in table]
    if last_nrows:
        extra = last_nrows - n
        if extra > 0: out += [f"{csi_clr}\n"] * extra
    last_nrows = n
    out.append("\x1B[?25h")
    sys.stdout.write("".join(out))
    sys.stdout.flush()

def draw_students(students): #таблица студентов
    orders = ['Очередь', 'Сдал', 'Провалил']
    students_sorted = sorted(students, key=lambda x: orders.index(x.get_status()))
    studlen = len('Студент')
    board = ['+--' + '-'*max(students[0].get_max_len(), studlen) + '+' + '-'*(len('Провалил') + 2) + '+',
             '| Студент' + ' '*max(students[0].get_max_len() - studlen, 0) + ' | ' + 'Статус'.center(len('Провалил')) + ' |',
             '+--' + '-'*max(students[0].get_max_len(), studlen) + '+' + '-'*(len('Провалил') + 2) + '+']
    waiting_studs = 0
    for student in students_sorted:
        if student.get_status() == orders[0]: waiting_studs += 1
        board.append(f'| {student.get_name()}' + ' '*(max(student.get_max_len(), studlen) - len(student.get_name())) +
                     f' | {student.get_status().center(len('Провалил'))} |')
    board.extend(['+--' + '-'*max(students[0].get_max_len(), studlen) + '+' + '-'*(len('Провалил') + 2) + '+'])
    return board, waiting_studs

def draw_examiners(examiners, max_stud): #таблица экзаменаторов
    examiners_sorted = sorted(examiners, key=lambda x: x.get_current_student(), reverse=True)
    board = ['+--' + '-'*max(examiners[0].get_max_len(), len('Экзаменатор')) + '+--' + '-'*max(max_stud, len('Текущий студент')) +
             '+--' + '-'*len('Всего студентов') + '+--' + '-'*len('Завалил') + '+--' + '-'*len('Время работы') + '+',
             '| Экзаменатор' + ' '*max(examiners[0].get_max_len() - len('Экзаменатор'), 0) + ' | Текущий студент' + ' '*max(max_stud - len('Текущий студент'), 0) +
             ' | Всего студентов | Завалил | Время работы |',
             '+--' + '-'*max(examiners[0].get_max_len(), len('Экзаменатор')) + '+--' + '-'*max(max_stud, len('Текущий студент')) +
             '+--' + '-'*len('Всего студентов') + '+--' + '-'*len('Завалил') + '+--' + '-'*len('Время работы') + '+']

    for examiner in examiners_sorted:
        board.append(f'| {examiner.get_name()}' + ' '*(max(examiner.get_max_len(), len('Экзаменатор')) - len(examiner.get_name())) +
                     f' | {examiner.get_current_student()}' + ' '*(max(max_stud, len('Текущий студент')) - len(examiner.get_current_student())) +
                     ' | ' + str(examiner.get_students_count()).center(len('Всего студентов')) +
                     ' | ' + str(examiner.get_failed()).center(len('Завалил')) +
                     ' | ' + str(examiner.get_worktime()).center(len('Время работы')) + ' |')
    board.extend(['+--' + '-'*max(examiners[0].get_max_len(), len('Экзаменатор')) + '+--' + '-'*max(max_stud, len('Текущий студент')) +
             '+--' + '-'*len('Всего студентов') + '+--' + '-'*len('Завалил') + '+--' + '-'*len('Время работы') + '+'])
    return board


def draw_final(students, examiners, continues, questions): #финальные таблицы
    # Таблица студентов
    orders = ['Очередь', 'Сдал', 'Провалил']
    students_sorted = sorted(students, key=lambda x: orders.index(x.get_status()))
    studlen = len('Студент')
    board = ['+--' + '-' * max(students[0].get_max_len(), studlen) + '+' + '-' * (len('Провалил') + 2) + '+',
             '| Студент' + ' ' * max(students[0].get_max_len() - studlen, 0) + ' | ' + 'Статус'.center(
                 len('Провалил')) + ' |',
             '+--' + '-' * max(students[0].get_max_len(), studlen) + '+' + '-' * (len('Провалил') + 2) + '+']

    for student in students_sorted:
        board.append(f'| {student.get_name()}' + ' ' * (max(student.get_max_len(), studlen) - len(student.get_name())) +
                     f' | {student.get_status().center(len("Провалил"))} |')
    board.extend(['+--' + '-' * max(students[0].get_max_len(), studlen) + '+' + '-' * (len('Провалил') + 2) + '+'])

    # Таблица экзаменаторов
    board.append('')
    board.append('+--' + '-' * max(examiners[0].get_max_len(), len('Экзаменатор')) +
                 '+--' + '-' * len('Всего студентов') + '+--' + '-' * len('Завалил') + '+--' + '-' * len(
        'Время работы') + '+')
    board.append('| Экзаменатор' + ' ' * max(examiners[0].get_max_len() - len('Экзаменатор'), 0) +
                 ' | Всего студентов | Завалил | Время работы |')
    board.append('+--' + '-' * max(examiners[0].get_max_len(), len('Экзаменатор')) +
                 '+--' + '-' * len('Всего студентов') + '+--' + '-' * len('Завалил') + '+--' + '-' * len(
        'Время работы') + '+')

    for examiner in examiners:
        board.append(f'| {examiner.get_name()}' + ' ' * (
                    max(examiner.get_max_len(), len('Экзаменатор')) - len(examiner.get_name())) +
                     ' | ' + str(examiner.get_students_count()).center(len('Всего студентов')) +
                     ' | ' + str(examiner.get_failed()).center(len('Завалил')) +
                     ' | ' + str(round(examiner.get_worktime(), 2)).center(len('Время работы')) + ' |')

    board.append('+--' + '-' * max(examiners[0].get_max_len(), len('Экзаменатор')) +
                 '+--' + '-' * len('Всего студентов') + '+--' + '-' * len('Завалил') + '+--' + '-' * len(
        'Время работы') + '+')

    # Итоговая статистика
    full_time = max(ex.get_worktime() for ex in examiners)
    suc_studs = [x for x in students if x.get_status() == 'Сдал']
    fail_studs = [x for x in students if x.get_status() == 'Провалил']

    # Лучшие студенты
    if suc_studs:
        min_stud_time = min(x.get_time() for x in suc_studs)
        best_students = [x.get_name() for x in suc_studs if x.get_time() == min_stud_time]
        best_studs_str = ", ".join(best_students)
    else:
        best_studs_str = "нет сдавших"

    # Лучшие экзаменаторы
    examiners_with_students = [ex for ex in examiners if ex.get_students_count() > 0]
    if examiners_with_students:
        min_fail_percent = min(ex.get_failed() / ex.get_students_count() for ex in examiners_with_students)
        best_examiners = [ex.get_name() for ex in examiners_with_students
                          if ex.get_failed() / ex.get_students_count() == min_fail_percent]
        best_exams_str = ", ".join(best_examiners)
    else:
        best_exams_str = "нет данных"

    # Отчисляемые студенты
    if fail_studs:
        max_stud_time = max(x.get_time() for x in fail_studs)
        expul_studs = [x.get_name() for x in fail_studs if x.get_time() == max_stud_time]
        expul_studs_str = ", ".join(expul_studs)
    else:
        expul_studs_str = "нет"

    # Лучшие вопросы
    if questions:
        max_successes = max(q.get_successes() for q in questions)
        best_questions_list = [q.get_text() for q in questions if q.get_successes() == max_successes]
        best_questions_str = ", ".join(best_questions_list)
    else:
        best_questions_str = "нет"

    # Вывод
    suc_studs_percent = round(len(suc_studs) / len(students) * 100) if students else 0
    conclusion = 'экзамен удался' if suc_studs_percent > 85 else 'экзамен не удался'

    # Отображение итогов
    board.extend([
        f'Время с момента начала экзамена и до момента его завершения: {round(full_time, 2)}',
        f'Имена лучших студентов: {best_studs_str}',
        f'Имена лучших экзаменаторов: {best_exams_str}',
        f'Имена студентов, которых после экзамена отчислят: {expul_studs_str}',
        f'Лучшие вопросы: {best_questions_str}',
        f'Вывод: {conclusion}'
    ])

    draw_change(board)


def new_exam_info(students, examiners, exam_start): #обновление таблицы
    cur_time = time.perf_counter()
    board, wait_studs = draw_students(students)
    board.extend(draw_examiners(examiners, students[0].get_max_len()))
    board.append(f'Осталось в очереди: {wait_studs} из {len(students)}')
    if wait_studs != 0:
        board.append(f'Время с момента начала экзамена: {round(cur_time - exam_start, 2)}')
    else:
        return round(cur_time - exam_start, 2)
    draw_change(board)
    return 0

def loop(students, examiners, questions, start): #цикл отображения
    continues = 0
    while continues == 0:
        continues = new_exam_info(students, examiners, start)
    draw_final(students, examiners, continues, questions)