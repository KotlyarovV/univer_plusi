#include <iostream>
#include <sstream>

template <typename T>
class Node {
public:
    Node<T>* next = NULL;
    Node<T>* previous = NULL;
    T value;

    Node(T value) {
        this->value = value;
    }
    // previous -- start -- next -- end
    void add_next(Node<T>* node) {
        this->next = node;
        if (node != nullptr) {
            node->previous = this;
        }
    }

    void add_previous(Node<T>* node) {
        this->previous = node;

        if (node != nullptr) {
            node->next = this;
        }
    }
};

template <typename T>
class LinkedList {
public:
    Node<T>* start = nullptr;

    Node<T>* end = nullptr;

    LinkedList<T>() {}

    ~LinkedList() {
        Node<T>* node = start;
        for (int i = 0; i < this->counter; i ++) {
            Node<T>* next = node->next;
            delete node;
            node = next;
        }
    }

    void sort() {
        for (int j = 0; j < counter; j++) {
            bool f = false;
            Node<T>* node = start;
            for (int i = 0; i < counter - j - 1; i++) {
                Node<T>* next = node->next;
                if (node->value >  node->next->value) {
                    next = node;
                    swap(node, node->next);
                    f = true;
                }
                node = next;
            }
            if (!f) break;
        }
    }

    void swap_neighbors(Node<T>* node1, Node<T>* node2) {
        Node<T> *node_previous = node1->previous;

        node1->add_next(node2->next);
        node1->add_previous(node2);

        node2->add_previous(node_previous);
        node2->add_next(node1);
    }

    void swap(Node<T>* node1, Node<T>* node2) {


        if (node1->next == node2) {
            swap_neighbors(node1, node2);
        }

        else if (node2->next == node1) {
            swap_neighbors(node2, node1);
        }

        else {
            Node<T> *node_previous = node1->previous;
            Node<T> *node_next = node1->next;

            node1->add_previous(node2->previous);
            node1->add_next(node2->next);

            node2->add_next(node_next);
            node2->add_previous(node_previous);
        }

        if (node1->previous == nullptr) {
            start = node1;
        }
        if (node1->next == nullptr) {
            end = node1;
        }
        if (node2->previous == nullptr) {
            start = node2;
        }
        if (node2->next == nullptr) {
            end = node2;
        }
    }

    void add_first(T value) {
        if (start == nullptr) {
            initialize_first(value);
        }
        else {
            start->previous = new Node<T>(value);
            start->previous->next = start;
            start = start->previous;
        }
        this->counter ++;
    }

    void remove_at(int i) {

        counter--;
        if (i == counter) {
            end = end->previous;
            delete end->next;
            end->next = NULL;
            return;
        }

        if (i == 0) {
            start = start->next;
            delete start->previous;
            start->previous = NULL;
            return;
        }

        int count = 0;
        auto* node = start;
        while (count < i) {
            node = node->next;
            count++;
        }

        node->next->add_previous(node->previous);
        node->previous->add_next(node->next);
        delete node;
    }

    void decrease_by_number() {
        int count = 0;
        for (auto* node = start; node != nullptr; node = node->next, count++) {
            node->value = node->value - count;
        }
    }

    void add_middle(T value) {
        if (start == nullptr) {
            initialize_first(value);
        }

        else {
            int middle = counter / 2;
            auto* node = start;
            int count = 0;
            while (count < middle - 1) {
                node = node->next;
                count++;
            }

            Node<T>* added_node = new Node<T>(value);
            added_node->add_next(node->next);
            added_node->add_previous(node);
        }
        this->counter++;
    }

    T at_index (int i) {
        int count = 0;
        auto* node = start;
        while (count < i) {
            node = node->next;
            count++;
        }
        return node->value;
    }

    int find_first(T e) {
        if (counter == 0)
            return -1;

        auto* node = start;
        int count = 0;

        for (auto* node = start; node != nullptr; node = node->next, count++) {
            if (node->value == e)
                return count;
        }

        return -1;
    }

    std::string to_string() {
        std::string result = "";
        for (auto* node = start; node != nullptr; node = node->next ) {
            std::stringstream string_pointer;
            string_pointer << node;
            result = result + std::to_string(node->value) + " " + "in address " + string_pointer.str() + "\n";
        }
        return result;
    }

private:
    int counter = 0;
    void initialize_first(T value) {
            start = new Node<T>(value);
            end = start;
    }
};

void add_first_elements(LinkedList<int>* list) {
    int count;
    std::cout << "Введите количество элементов" << std::endl;
    std::cin >> count;
    std::cout << std::endl;

    std::cout << "Введеные вами элементы будут вставлены в начало списка" << std::endl;

    for (int i = 0; i < count; ++i) {
        std::cout << "Введите число" << std::endl;
        int element;
        std::cin >> element;
        std::cout << std::endl;
        list->add_first(element);
    }
}

void add_middle_elements(LinkedList<int>* list) {
    std::cout << "Введите количество элементов для вставки в середину списка" << std::endl;
    int count;
    std::cin >> count;
    std::cout << std::endl;


    for (int i = 0; i < count; ++i) {
        std::cout << "Введите число" << std::endl;
        int element;
        std::cin >> element;
        std::cout << std::endl;
        list->add_middle(element);
    }
}

std::string menu() {

    std::string messages[8] = {
            "Для сортировки списка нажмите 1",
            "Для удаления из списка элемнта по индексу нажмите 2",
            "Для уменьшения каждого элемента на его порядковый номер нажмите 3",
            "Для выведения элемента по его индексу нажмите 4",
            "Чтобы вывести индекс по элементу нажмите 5 (при отсутствии элемента будет выведено -1)",
            "Для записи элементов в начало списка нажмите 6",
            "Для записи элементов в середину списка нажмите 7",
            "Для остановки программы нажмите 8"
    };

    std::string result = "";
    for (int i = 0; i < 8; i++) {
        result = result + messages[i] + "\n";
    }
    return result;
}

int main() {


    auto* list = new LinkedList<int>();

    add_first_elements(list);
    std::cout << "Введеные Вами элементы" << std::endl;
    std::cout << list->to_string() << std::endl;

    while (true) {
        std::cout << menu() << std::endl;
        int choice;
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1: {
                list->sort();
                break;
            }
            case 2: {
                std::cout << "Введите индекс элемента для удаления" <<  std::endl;
                int  i ;
                std::cin >> i;
                list->remove_at(i);
                break;
            }
            case 3:
                list->decrease_by_number();
                break;
            case 4: {
                std::cout << "Введите индекс элемента для вывода" << std::endl;
                int  i ;
                std::cin >> i;
                std::cout << list->at_index(i) << std::endl;
                break;
            }
            case 5: {
                std::cout << "Введите элемент для вывода индекса" << std::endl;
                int  i ;
                std::cin >> i;
                std::cout << list->find_first(i) << std::endl;
                break;
            }
            case 6: {
                add_first_elements(list);
                break;
            }
            case 7: {
                add_middle_elements(list);
                break;
            }
            case 8:
                return 0;
            default:
                std::cout << "Вы ввели неверное число" << std::endl;
                break;

        }
        if (choice != 4 && choice != 5) {
            std::cout << "Текущее состояние списка" << std::endl;
            std::cout << list->to_string() << std::endl;
        }

    }

}