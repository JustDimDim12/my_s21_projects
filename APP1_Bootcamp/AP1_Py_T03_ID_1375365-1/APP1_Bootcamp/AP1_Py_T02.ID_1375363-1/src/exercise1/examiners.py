import time

class Examiner:
    max_len = 0

    def __init__(self, name, gender):
        self.name = name
        self.gender = gender
        self.current_student = '-'
        self.students_count = 0
        self.failed = 0
        self.start_time = time.perf_counter()
        self.stop_time = 0
        self.isRested = False
        if len(name) > Examiner.max_len:
            Examiner.max_len = len(name)

    def get_name(self):
        return self.name

    def get_gender(self):
        return self.gender

    def get_current_student(self):
        return self.current_student

    def set_current_student(self, current_student):
        self.current_student = current_student

    def get_students_count(self):
        return self.students_count

    def new_student(self):
        self.students_count += 1

    def get_failed(self):
        return self.failed

    def new_fail(self):
        self.failed += 1

    def time_starts(self, start):
        self.start_time = start

    def time_stop(self):
        self.stop_time = time.perf_counter()

    def resume_time(self):
        if self.stop_time > 0:
            worked = time.perf_counter() - self.stop_time
            self.start_time += worked
            self.stop_time = 0

    def get_worktime(self):
        if self.stop_time > 0:
            return round(self.stop_time - self.start_time, 2)
        else:
            return round(time.perf_counter() - self.start_time, 2)

    def get_rested(self):
        return self.isRested

    def set_rested(self):
        self.isRested = True

    def get_max_len(self):
        return Examiner.max_len