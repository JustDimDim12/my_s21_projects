class Question:
    def __init__(self, text):
        self.words = text.split()
        self.successes = 0

    def get_words(self):
        return self.words

    def get_text(self):
        return ' '.join(self.words)

    def get_successes(self):
        return self.successes

    def new_success(self):
        self.successes += 1