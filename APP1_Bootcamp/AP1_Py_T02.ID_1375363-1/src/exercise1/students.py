class Student:
    max_len = 0

    def __init__(self, name, gender):
        self.name = name
        self.gender = gender
        self.isPassing = False
        self.time = 0
        self.right_answers = 0
        self.status = 'Очередь'
        if len(name) > Student.max_len:
            Student.max_len = len(name)

    def get_name(self):
        return self.name

    def get_gender(self):
        return self.gender

    def get_passing(self):
        return self.isPassing

    def set_passing(self):
        self.isPassing = True

    def get_right_answers(self):
        return self.right_answers

    def set_right_answers(self, answers):
        self.right_answers = answers

    def get_time(self):
        return self.time

    def set_time(self, time):
        self.time = time

    def get_status(self):
        return self.status

    def set_status(self, status):
        self.status = status

    def get_max_len(self):
        return Student.max_len