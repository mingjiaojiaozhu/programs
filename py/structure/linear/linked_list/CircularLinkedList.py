#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class CircularLinkedList:
    def isCircular(self, head: ListNode) -> bool:
        slow, fast = head.next, head.next
        while fast and fast.next:
            slow, fast = slow.next, fast.next.next
            if slow == fast:
                return True
        return False

    def circularLength(self, head: ListNode) -> int:
        slow, fast = head.next, head.next
        while fast and fast.next:
            slow, fast = slow.next, fast.next.next
            if slow == fast:
                break

        if not fast or not fast.next:
            return 0

        slow, count = slow.next, 1
        while slow != fast:
            slow = slow.next
            count += 1
        return count

    def circularEntry(self, head: ListNode) -> ListNode:
        slow, fast = head.next, head.next
        while fast and fast.next:
            slow, fast = slow.next, fast.next.next
            if slow == fast:
                break

        if not fast or not fast.next:
            return None

        fast = head.next
        while slow != fast:
            slow, fast = slow.next, fast.next
        return slow
