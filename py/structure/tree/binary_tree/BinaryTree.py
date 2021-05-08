#!/usr/bin/env python
# -*- coding:gbk -*-

class TreeNode:
    def __init__(self, value: int):
        self.value, self.left, self.right = value, None, None

class BinaryTree:
    def isPerfect(self, root: TreeNode) -> bool:
        if not root:
            return True

        queue = [root]
        count, flag = 0, False
        while queue:
            current = queue.pop(0)
            if not current:
                flag = True
                continue

            if flag:
                return False

            count += 1
            queue.append(current.left)
            queue.append(current.right)
        return not (count & (count + 1))

    def isCompleted(self, root: TreeNode) -> bool:
        if not root:
            return True

        queue = [root]
        flag = False
        while queue:
            current = queue.pop(0)
            if (not current.left and current.right) or (flag and (current.left or current.right)):
                return False

            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)
            else:
                flag = True
        return True

    def isFull(self, root: TreeNode) -> bool:
        if not root:
            return True

        queue = [root]
        while queue:
            current = queue.pop(0)
            if (current.left and not current.right) or (not current.left and current.right):
                return False

            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)
        return True

    def nodeNum(self, root: TreeNode) -> int:
        if not root:
            return 0

        queue = [root]
        count = 0
        while queue:
            count += 1

            current = queue.pop(0)
            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)
        return count

    def leafNodeNum(self, root: TreeNode) -> int:
        if not root:
            return 0

        queue = [root]
        count = 0
        while queue:
            current = queue.pop(0)
            if not current.left and not current.right:
                count += 1
                continue

            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)
        return count

    def maxDepth(self, root: TreeNode) -> int:
        if not root:
            return 0

        queue = [root]
        count = 0
        while queue:
            count += 1

            length = len(queue)
            for _ in range(length):
                current = queue.pop(0)
                if current.left:
                    queue.append(current.left)
                if current.right:
                    queue.append(current.right)
        return count

    def mirror(self, root: TreeNode) -> TreeNode:
        if not root or (not root.left and not root.right):
            return root

        root.left, root.right = root.right, root.left
        root.left, root.right = self.mirror(root.left), self.mirror(root.right)
        return root
