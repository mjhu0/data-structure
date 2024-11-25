class Student:
    def __init__(self, student_id, name, gender, age, phone, major, class_name):
        self.student_id = student_id  # 学号
        self.name = name              # 姓名
        self.gender = gender          # 性别
        self.age = age                # 年龄
        self.phone = phone            # 电话号码
        self.major = major            # 专业
        self.class_name = class_name  # 班级
        self.next = None              # 指向下一个学生的指针（用于链表）

class StudentManagementSystem:
    def __init__(self):
        self.head = None  # 链表头节点

    def create_student(self, student_id, name, gender, age, phone, major, class_name):
        """创建并添加学生信息到链表"""
        new_student = Student(student_id, name, gender, age, phone, major, class_name)
        if self.head is None:
            self.head = new_student
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_student
###########               胡华吉  542313460109        ####################
    def display_students(self):
        """输出所有学生信息"""
        if self.head is None:
            print("没有学生信息。")
            return
        current = self.head
        while current:
            print(f"学号: {current.student_id}, 姓名: {current.name}, 性别: {current.gender}, 年龄: {current.age}, 电话: {current.phone}, 专业: {current.major}, 班级: {current.class_name}")
            current = current.next

    def find_student(self, student_id):
        """查询学生信息"""
        current = self.head
        while current:
            if current.student_id == student_id:
                print(f"学号: {current.student_id}, 姓名: {current.name}, 性别: {current.gender}, 年龄: {current.age}, 电话: {current.phone}, 专业: {current.major}, 班级: {current.class_name}")
                return current
            current = current.next
        print("未找到该学生。")
        return None

    def add_student(self, student_id, name, gender, age, phone, major, class_name):
        """增加新的学生信息"""
        self.create_student(student_id, name, gender, age, phone, major, class_name)
        print(f"学生 {name} 已添加。")

    def delete_student(self, student_id):
        """删除学生信息"""
        current = self.head
        previous = None
        while current:
            if current.student_id == student_id:
                if previous is None:  # 要删除的是头节点
                    self.head = current.next
                else:
                    previous.next = current.next
                print(f"学生 {current.name} 已删除。")
                return
            previous = current
            current = current.next
        print("未找到该学生，无法删除。")

# 示例操作
sms = StudentManagementSystem()
sms.create_student("1001", "张三", "男", 20, "1234567890", "计算机科学", "1班")
sms.create_student("1002", "李四", "女", 21, "0987654321", "软件工程", "2班")

print("所有学生信息：")
sms.display_students()

print("\n查询学号为1001的学生：")
sms.find_student("1001")

print("\n增加新的学生：")
sms.add_student("1003", "王五", "男", 22, "1122334455", "信息安全", "3班")
sms.display_students()

print("\n删除学号为1002的学生：")
sms.delete_student("1002")
sms.display_students()