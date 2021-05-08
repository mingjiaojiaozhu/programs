#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class SequenceSearch:
    def search(self, head: ListNode, target: int) -> ListNode:
        current = head.next
        while current:
            if target == current.value:
                return current
            current = current.next
        return None
