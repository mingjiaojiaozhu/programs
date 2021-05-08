#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class InsertionSort:
    def sort(self, head: ListNode) -> None:
        current = head.next
        while current.next:
            prev = head
            while prev != current and prev.next.value <= current.next.value:
                prev = prev.next

            if prev == current:
                current = current.next
            else:
                next = current.next
                current.next, next.next, prev.next = next.next, prev.next, next
