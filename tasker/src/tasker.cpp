#include <iostream>
#include <tuple>
#include <map>
#include <vector>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

// Выделим в отдельную функцию получение следующего по приоритету типа задачи
// Функция налагает требование на входной параметр: он не должен быть равен DONE
// При этом task_status явно не сравнивается с DONE, что позволяет
// сделать эту функцию максимально эффективной
TaskStatus Next(TaskStatus task_status) {
	return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string &person) const;

	// Добавить новую задачу (в статусе NEW) для конкретного разработчика
	void AddNewTask(const string &person);

	// Обновить статусы по данному количеству задач конкретного разработчика
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person,
			int task_count);

private:
	map<string, TasksInfo> person_tasks_;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string &person) const {
	return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string &person) {
	++person_tasks_[person][TaskStatus::NEW];
}

// Функция для удаления нулей из словаря
void RemoveZeros(TasksInfo &tasks_info) {
	// Соберём те статусы, которые нужно убрать из словаря
	vector<TaskStatus> statuses_to_remove;
	for (const auto &task_item : tasks_info) {
		if (task_item.second == 0) {
			statuses_to_remove.push_back(task_item.first);
		}
	}
	for (const TaskStatus status : statuses_to_remove) {
		tasks_info.erase(status);
	}
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string &person,
		int task_count) {
	TasksInfo updated_tasks, untouched_tasks;

	// Здесь и далее мы будем пользоваться тем фактом, что в std::map оператор []
	// в случае отсутствия ключа инициализирует значение по умолчанию,
	// если это возможно.
	// std::map::operator[] ->
	// http://ru.cppreference.com/w/cpp/container/map/operator_at
	TasksInfo &tasks = person_tasks_[person];

	// Посчитаем, сколько задач каждого из статусов нужно обновить,
	// пользуясь тем фактом, что по умолчанию enum class инциализирует значения
	// от нуля по возрастанию.
	// enum class -> http://ru.cppreference.com/w/cpp/language/enum
	for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE;
			status = Next(status)) {
		// Считаем обновлённые
		updated_tasks[Next(status)] = min(task_count, tasks[status]);
		// Считаем, сколько осталось обновить
		task_count -= updated_tasks[Next(status)];
	}

	// Обновляем статус текущих задач в соответствии с информацией об обновлённых
	// и находим количество нетронутых
	for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE;
			status = Next(status)) {
		untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
		tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
	}
	// По условию, DONE задачи не нужно возвращать в не обновлённых задачах
	tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

	// По условию в словарях не должно быть нулей
	RemoveZeros(updated_tasks);
	RemoveZeros(untouched_tasks);
	RemoveZeros(person_tasks_.at(person));

	return {updated_tasks, untouched_tasks};
}
// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(const TasksInfo &tasks_info) {
	if (tasks_info.count(TaskStatus::NEW)) {
		std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
	}
	if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
		std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS)
				<< " ";
	}
	if (tasks_info.count(TaskStatus::TESTING)) {
		std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
	}
	if (tasks_info.count(TaskStatus::DONE)) {
		std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
	}
}

void PrintTasksInfo(const TasksInfo &updated_tasks,
		const TasksInfo &untouched_tasks) {
	std::cout << "Updated: [";
	PrintTasksInfo(updated_tasks);
	std::cout << "] ";

	std::cout << "Untouched: [";
	PrintTasksInfo(untouched_tasks);
	std::cout << "] ";

	std::cout << std::endl;
}

int main() {
	TeamTasks tasks;
	TasksInfo updated_tasks;
	TasksInfo untouched_tasks;

	/* TEST 1 */
	std::cout << "Alice" << std::endl;

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks); // [{"DONE": 1}, {"TESTING": 4}]

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2); // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
	PrintTasksInfo(updated_tasks, untouched_tasks);

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice")); // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
	PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice")); // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	std::cout << std::endl;

	/* TEST 2 */
	std::cout << "\nJack" << std::endl;

	tasks.AddNewTask("Jack");

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	tasks.AddNewTask("Jack");

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

	tasks.AddNewTask("Jack");

	PrintTasksInfo(tasks.GetPersonTasksInfo("Jack")); // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
	PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Jack")); // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
	std::cout << std::endl;

	/* TEST 3 */
	std::cout << "\nLisa" << std::endl;

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Lisa");
	}

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks); // [{"DONE": 1}, {"TESTING": 4}]

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Lisa");
	}

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
	PrintTasksInfo(updated_tasks, untouched_tasks); // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks); // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"TESTING": 8, "DONE": 2}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	std::cout << std::endl;

	tasks.AddNewTask("Lisa");

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa")); // {"IN_PROGRESS": 1, "DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	return 0;
}
