from examiners import Examiner
from students import Student
from questions import Question

from random import random, randint, shuffle, uniform
import time

def probabilities(len_w, gender, gold_sech): #определение вероятности по гендеру студента
    probs = []
    lost_prob = 1.0

    for i in range(len_w):
        if i == len_w - 1:
            prob = lost_prob
        else:
            prob = lost_prob / gold_sech
            lost_prob -= prob
        probs.append(prob)

    if gender == 'female':
        probs.reverse()
    return probs

def the_st_answer(words, gender): #ответы студента
    gold_sech = (1 + 5**0.5) / 2 #золотое сечение
    len_w = len(words)
    probs = probabilities(len_w, gender, gold_sech)

    res = 0
    rand_val = random()
    need_prob = 0
    for i, prob in enumerate(probs):
        need_prob += prob
        if rand_val < need_prob:
            res = words[i]
            break

    if res == 0:
        res = words[-1]

    return res

def the_ex_answers(Words): #ответы экзаменатора
    words = Words.copy()
    ex_answers = [words.pop(randint(0, len(words) - 1))]
    while words and random() < 1/3:
        ex_answers.append(words.pop(randint(0, len(words) - 1)))
    return ex_answers


def asking(examiner, student, questions, start): #студенту задаются вопросы
    shuffle(questions)
    success_count = 0

    name_len = len(examiner.get_name())
    total_duration = uniform(name_len - 1, name_len + 1)

    # Время на один вопрос
    time_per_question = total_duration / len(questions)

    for i, question in enumerate(questions):
        q = question.get_words()

        # Задержка на ответ
        time.sleep(uniform(time_per_question * 0.8, time_per_question * 1.2))

        st_answer = the_st_answer(q, student.get_gender())
        ex_answers = the_ex_answers(q)

        if st_answer in ex_answers:
            success_count += 1
            question.new_success()

    return success_count

def finalize(examiner, student, questions, success_count, start): #резюмирование результатов
    # Настроение экзаменатора
    mood = random()
    end_time = time.perf_counter()

    if mood < 1 / 8:
        student.set_status('Провалил')
        examiner.new_fail()
    elif mood < 1 / 8 + 1 / 4:
        student.set_status('Сдал')
    else:
        if success_count > len(questions) - success_count:
            student.set_status('Сдал')
        else:
            student.set_status('Провалил')
            examiner.new_fail()

    student.set_time(end_time - start)
    examiner.new_student()

def concrete_exam(examiner, student, questions): #конкретный экзамен
    start = time.perf_counter()
    examiner.set_current_student(student.get_name())
    student.set_passing()

    success_count = asking(examiner, student, questions, start)
    student.set_right_answers(success_count)
    finalize(examiner, student, questions, success_count, start)
    examiner.set_current_student('-')

def free_st_index(ex_id, students): #индекс свободного студента
    for i in range(ex_id, len(students)):
        if not students[i].get_passing() and students[i].get_status() == 'Очередь':
            return i
    return None

def check_rest(ex): #проверка на надобность отдыха
    if ex.get_worktime() > 30 and not ex.get_rested():
        ex.time_stop()
        ex.set_current_student('-')
        time.sleep(randint(12, 18))
        ex.resume_time()
        ex.setRested()


def current(examiner, student_queue, questions): #течение экзамена
    examiner.time_starts(time.perf_counter())

    while True:
        try:
            student = student_queue.get_nowait()
            concrete_exam(examiner, student, questions)
            check_rest(examiner)
        except:
            break

    examiner.time_stop()
    examiner.set_current_student('-')