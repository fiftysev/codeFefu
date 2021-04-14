from random import randint
import collections


class Pass:
    def __init__(self, document_id, level):
        self.document_id = document_id
        self.level = level


class Book:
    def __init__(self, document_id):
        self.document_id = document_id
        self.marks = dict()


class Lecture:
    def __init__(self, subject, quality):
        self.subject = subject
        self.quality = quality


class Person:
    def __init__(self, full_name, pass_card=None):
        self.pass_card = Pass(0, 0) if not pass_card else pass_card
        self.full_name = full_name

    def show_pass(self):
        return self.pass_card


class Student(Person):
    def __init__(self, full_name, pass_card, book):
        super().__init__(full_name, pass_card)

        self.book = book
        self.knowledge = collections.defaultdict(int)

    def __add__(self, other):
        if isinstance(other, Student):
            return Group(self, other)
        if isinstance(other, Group):
            return Group(*other.get_group(), self)

    def listen_to_lecture(self, lecture):
        self.knowledge[lecture.subject] += randint(0, 1) * lecture.quality

    def get_marks(self):
        return self.book.marks


class Group:
    def __init__(self, *students, name=None):
        self._students = list(*students)
        self._name = name

    def __add__(self, other):
        if isinstance(other, Student):
            return Group(self, other)
        if isinstance(other, Group):
            return Group(*other.get_group(), *self.get_group())

    def get_group(self):
        return self._students[:]

    def __iter__(self):
        return iter(self.get_group())


class Teacher(Person):
    def __init__(self, full_name, pass_card, subject):
        super().__init__(full_name, pass_card)
        self.subject = subject

    def make_lecture(self):
        return Lecture(self.subject, randint(0, 1))

    def examine(self, group):
        if isinstance(group, Student):
            group.book.marks[self.subject] = randint(2, 5) * group.knowledge[self.subject]

        if isinstance(group, Group):
            for student in group:
                self.examine(student)


if __name__ == '__main__':
    math_teacher = Teacher("Klevch", Pass(123, 1), "math")
    me = Student("Misha Ruzin", Pass(47, 2), Book(47))
    me.listen_to_lecture(math_teacher.make_lecture())
    math_teacher.examine(me)
    print(me.get_marks())
