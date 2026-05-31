import time
from multiprocessing import Process, Queue, Lock
from multiprocessing.managers import BaseManager

from students import Student
from examiners import Examiner
from questions import Question
from draw import loop
from exam_process import current

def loading_base(): #импорт данных студентов из файлов
    BaseManager.register('Student', Student)
    BaseManager.register('Examiner', Examiner)
    BaseManager.register('Question', Question)
    manager = BaseManager()
    manager.start()

    students = []
    examiners = []
    questions = []

    with open("students.txt", "r", encoding='utf-8') as f:
        for line in f.readlines():
            name, gender = line.split()
            students.append(manager.Student(name, gender))

    with open("examiners.txt", "r", encoding='utf-8') as f:
        for line in f.readlines():
            name, gender = line.split()
            examiners.append(manager.Examiner(name, gender))

    with open("questions.txt", "r", encoding='utf-8') as f:
        for line in f.readlines():
            questions.append(manager.Question(line))

    return students, examiners, questions

def main():
    start = time.perf_counter()
    students, examiners, questions = loading_base()

    # Заполнение очереди студентами
    student_queue = Queue()
    for student in students:
        student_queue.put(student)

    processes = []
    for examiner in examiners:
        processes.append(Process(target=current, args=(examiner, student_queue, questions)))
    draw_process = Process(target=loop, args=(students, examiners, questions, start))

    for p in processes:
        p.start()
    time.sleep(0.2)
    draw_process.start()

    for p in processes:
        p.join()
    draw_process.join()

if __name__ == '__main__':
    main()