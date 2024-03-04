#ifndef PROJECT_BASE_LISTATCB_HPP
#define PROJECT_BASE_LISTATCB_HPP

class TCB;

class ListaTCB
{
private:
    struct Elem
    {
        TCB *data;
        Elem *next;

        Elem(TCB *data, Elem *next) : data(data), next(next) {}
    };

    Elem *head, *tail;

public:
    ListaTCB() : head(0), tail(0) {}

    ListaTCB(const ListaTCB &) = delete;

    ListaTCB &operator=(const ListaTCB &) = delete;

    void addFirst(TCB *data)
    {
        Elem *elem = new Elem(data, head);
        head = elem;
        if (!tail) { tail = head; }
    }

    void addLast(TCB *data)
    {
        Elem *elem = new Elem(data, 0);
        if (tail)
        {
            tail->next = elem;
            tail = elem;
        } else
        {
            head = tail = elem;
        }
    }

    TCB *removeFirst()
    {
        if (!head) { return 0; }

        Elem *elem = head;
        head = head->next;
        if (!head) { tail = 0; }

        TCB *ret = elem->data;
        delete elem;
        return ret;
    }

    TCB *peekFirst()
    {
        if (!head) { return 0; }
        return head->data;
    }

    TCB *removeLast()
    {
        if (!head) { return 0; }

        Elem *prev = 0;
        for (Elem *curr = head; curr && curr != tail; curr = curr->next)
        {
            prev = curr;
        }

        Elem *elem = tail;
        if (prev) { prev->next = 0; }
        else { head = 0; }
        tail = prev;

        TCB *ret = elem->data;
        delete elem;
        return ret;
    }

    TCB *peekLast()
    {
        if (!tail) { return 0; }
        return tail->data;
    }
};

#endif //PROJECT_BASE_LISTATCB_HPP
