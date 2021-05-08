#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class SelectionSort:
    def sort(self, head: ListNode) -> None:
        prev = head
        while prev.next:
            current, node = prev, prev.next
            while node.next:
                if current.next.value > node.next.value:
                    current = node
                node = node.next

            if prev != current:
                next = current.next
                current.next, next.next, prev.next = next.next, prev.next, next
            prev = prev.next
