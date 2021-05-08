* 0.数学
  * 0.素数筛选法
    * [0.Eratosthenes筛选法](math/EratosthenesSieve.py)
    * [1.Euler筛](math/EulerSieve.py)
  * [1.Euclidean算法(GCD&LCM)](math/Euclidean.py)
  * [2.扩展Euclidean算法](math/ExtendedEuclidean.py)
  * [3.中国剩余定理(CRT)](math/CRT.py)
  * [4.Euler函数](math/EulerTotientFunction.py)
  * [5.Rabin-Miller大素数判定](math/RabinMiller.py)
  * [6.Pollard-rho大数因式分解](math/PollardRho.py)
* 1.数据结构
  * 0.线形结构
    * [0.数组](structure/linear/Array.py)
    * 1.链表
      * [0.单链表](structure/linear/linked_list/SinglyLinkedList.py)
      * [1.双链表](structure/linear/linked_list/DoublyLinkedList.py)
      * [2.跳表](structure/linear/linked_list/SkipList.py)
      * [3.环形链表](structure/linear/linked_list/CircularLinkedList.py)
    * 2.栈
      * [0.基于数组](structure/linear/stack/StackOfArray.py)
      * [1.基于链表](structure/linear/stack/StackOfLinkedList.py)
    * 3.队列
      * 0.单向队列
        * [0.基于数组](structure/linear/queue/QueueOfArray.py)
        * [1.基于链表](structure/linear/queue/QueueOfLinkedList.py)
      * 1.双向队列
        * [0.基于数组](structure/linear/queue/DequeOfArray.py)
        * [1.基于链表](structure/linear/queue/DequeOfLinkedList.py)
      * [2.优先队列](structure/linear/queue/PriorityQueue.py)
  * 1.树形结构
    * [0.二叉树](structure/tree/binary_tree/BinaryTree.py)
      * 0.遍历
        * [0.前序遍历](structure/tree/binary_tree/traversal/PreOrderTraversal.py)
          * [0.Morris](structure/tree/binary_tree/traversal/morris/PreOrderTraversal.py)
        * [1.中序遍历](structure/tree/binary_tree/traversal/InOrderTraversal.py)
          * [0.Morris](structure/tree/binary_tree/traversal/morris/InOrderTraversal.py)
        * [2.后序遍历](structure/tree/binary_tree/traversal/PostOrderTraversal.py)
          * [0.Morris](structure/tree/binary_tree/traversal/morris/PostOrderTraversal.py)
        * [3.层序遍历](structure/tree/binary_tree/traversal/LevelOrderTraversal.py)
      * 1.重建
        * [0.基于前序和中序遍历](structure/tree/binary_tree/rebuild/RebuildOfPreAndInOrder.py)
        * [0.基于中序和后序遍历](structure/tree/binary_tree/rebuild/RebuildOfInAndPostOrder.py)
    * 1.检索树
      * [0.二叉检索树](structure/tree/search_tree/BinarySearchTree.py)
      * [1.树堆](structure/tree/search_tree/Treap.py)
      * [2.伸展树](structure/tree/search_tree/SplayTree.py)
      * [3.平衡二叉树(AVL)](structure/tree/search_tree/AVLTree.py)
      * [4.红黑树](structure/tree/search_tree/RedBlackTree.py)
      * [5.B树](structure/tree/search_tree/BTree.py)
      * [6.B+树](structure/tree/search_tree/BPlusTree.py)
    * [2.字典树](structure/tree/TrieTree.py)
    * [3.线段树](structure/tree/SegmentTree.py)
    * 4.堆
      * [0.二叉堆](structure/tree/heap/BinaryHeap.py)
      * [1.二项堆](structure/tree/heap/BinomialHeap.py)
      * [2.Fibonacci堆](structure/tree/heap/FibonacciHeap.py)
      * [3.配对堆](structure/tree/heap/PairingHeap.py)
  * 2.图形结构
    * [0.邻接矩阵](structure/graph/GraphOfAdjacencyMatrix.py)
    * [1.邻接表](structure/graph/GraphOfAdjacencyList.py)
  * 3.集合结构
    * 0.散列表
      * [0.开放地址法](structure/set/hash/HashOfOpenAddress.py)
      * [1.链地址法](structure/set/hash/HashOfChainAddress.py)
    * [1.LRU缓存](structure/set/LRUCache.py)
    * [2.位图](structure/set/BitMap.py)
    * [3.Bloom过滤器](structure/set/BloomFilter.py)
    * [4.并查集](structure/set/UnionFind.py)
* 2.排序
  * 0.数组
    * [0.冒泡排序](sort/array/BubbleSort.py)
    * [1.选择排序](sort/array/SelectionSort.py)
    * [2.插入排序](sort/array/InsertionSort.py)
    * [3.Shell排序](sort/array/ShellSort.py)
    * [4.堆排序](sort/array/HeapSort.py)
    * [5.快速排序](sort/array/QuickSort.py)
    * [6.归并排序](sort/array/MergeSort.py)
    * [7.计数排序](sort/array/CountingSort.py)
    * [8.桶排序](sort/array/BucketSort.py)
    * [9.基数排序](sort/array/RadixSort.py)
    * [A.完美排序](sort/array/StoogeSort.py)
    * [B.鸡尾酒排序](sort/array/CocktailSort.py)
    * [C.地精排序](sort/array/GnomeSort.py)
    * [D.原地归并排序](sort/array/MergeInPlaceSort.py)
    * [E.煎饼排序](sort/array/PancakeSort.py)
    * [F.Tim排序](sort/array/TimSort.py)
  * 1.链表
    * [0.冒泡排序](sort/linked_list/BubbleSort.py)
    * [1.选择排序](sort/linked_list/SelectionSort.py)
    * [2.插入排序](sort/linked_list/InsertionSort.py)
    * [3.快速排序](sort/linked_list/QuickSort.py)
    * [4.归并排序](sort/linked_list/MergeSort.py)
    * [5.基数排序](sort/linked_list/RadixSort.py)
  * 2.字符串
    * [0.LSD基数排序](sort/string/LSDRadixSort.py)
    * [1.MSD基数排序](sort/string/MSDRadixSort.py)
    * [2.快速排序](sort/string/QuickSort.py)
  * [3.外部排序](sort/ExternalSort.py)
  * 4.随机排序(洗牌算法)
    * [0.Fisher-Yates](sort/shuffle/FisherYates.py)
    * [1.Knuth-Durstenfeld](sort/shuffle/KnuthDurstenfeld.py)
    * [2.Inside-Out](sort/shuffle/InsideOut.py)
* 3.查找
  * 0.数组
    * [0.顺序查找](search/array/SequenceSearch.py)
    * [1.二分法查找](search/array/BinarySearch.py)
    * [2.插值查找](search/array/InterpolationSearch.py)
    * [3.Fibonacci查找](search/array/FibonacciSearch.py)
    * [4.跳跃查找](search/array/JumpSearch.py)
    * [5.分块查找](search/array/BlockingSearch.py)
  * 1.链表
    * [0.顺序查找](search/linked_list/SequenceSearch.py)
    * [1.二分法查找](search/linked_list/BinarySearch.py)
  * 2.字符串
    * [0.Brute-Force(BF)](search/string/BruteForce.py)
    * [1.Rabin-Karp(RK)](search/string/RabinKarp.py)
    * [2.Knuth-Morris-Pratt(KMP)](search/string/KnuthMorrisPratt.py)
    * [3.Boyer-Moore(BM)](search/string/BoyerMoore.py)
    * [4.Sunday](search/string/Sunday.py)
    * [5.Horspool](search/string/Horspool.py)
    * [6.Aho-Corasick(AC自动机)](search/string/AhoCorasick.py)
  * 3.top k
    * [0.堆选择](search/top_k/HeapSelect.py)
    * [1.随机选择](search/top_k/QuickSelect.py)
    * [2.线性时间选择(BFPRT)](search/top_k/BFPRTSelect.py)
* 4.图
  * 0.遍历
    * [0.深度优先遍历(DFS)](graph/traversal/DFS.py)
    * [1.广度优先遍历(BFS)](graph/traversal/BFS.py)
  * 1.最短路径
    * [0.Dijkstra](graph/shortest_path/Dijkstra.py)
    * [1.Bellman-Ford(BF)](graph/shortest_path/BellmanFord.py)
    * [2.最短路径快速算法(SPFA)](graph/shortest_path/SPFA.py)
    * [3.Floyd-Warshall](graph/shortest_path/FloydWarshall.py)
    * [4.Johnson](graph/shortest_path/Johnson.py)
    * [5.A*](graph/shortest_path/AStar.py)
  * 2.最小生成树
    * [0.Prim](graph/minimum_spanning_tree/Prim.py)
    * [1.Kruskal](graph/minimum_spanning_tree/Kruskal.py)
    * [2.Boruvka](graph/minimum_spanning_tree/Boruvka.py)
  * 3.强连通分量
    * [0.Kosaraju-Sharir](graph/strongly_connected_component/KosarajuSharir.py)
    * [1.Tarjan](graph/strongly_connected_component/Tarjan.py)
    * [2.Gabow](graph/strongly_connected_component/Gabow.py)
  * [4.拓扑排序](graph/topological_sort/TopologicalSort.py)
    * [0.Kahn](graph/topological_sort/Kahn.py)
  * [5.关键路径](graph/CriticalPath.py)
  * 6.Euler路径
    * [0.无向图](graph/eulerian_path/undirected/EulerianPath.py)
      * [0.Fleury](graph/eulerian_path/undirected/Fleury.py)
      * [1.Hierholzer](graph/eulerian_path/undirected/Hierholzer.py)
    * [1.有向图](graph/eulerian_path/directed/EulerianPath.py)
      * [0.Fleury](graph/eulerian_path/directed/Fleury.py)
      * [1.Hierholzer](graph/eulerian_path/directed/Hierholzer.py)
  * 7.最大流
    * [0.Ford-Fulkerson(FFA)](graph/maximum_flow/FordFulkerson.py)
    * [1.Edmonds-Karp(EK)](graph/maximum_flow/EdmondsKarp.py)
    * [2.Dinic](graph/maximum_flow/Dinic.py)
    * [3.最短增广路(SAP)](graph/maximum_flow/SAP.py)
    * [4.最高标号预流推进(HLPP)](graph/maximum_flow/HLPP.py)
  * 8.最小费用最大流
    * [0.Dijkstra](graph/minimum_cost_maximum_flow/Dijkstra.py)
    * [1.Bellman-Ford(BF)](graph/minimum_cost_maximum_flow/BellmanFord.py)
    * [2.最短路径快速算法(SPFA)](graph/minimum_cost_maximum_flow/SPFA.py)
    * [3.Dinic](graph/minimum_cost_maximum_flow/Dinic.py)
  * 9.最大匹配
    * [0.匈牙利算法](graph/maximum_matching/Hungary.py)
    * [1.Kuhn-Munkres(KM)](graph/maximum_matching/KuhnMunkres.py)
* 5.五大经典算法
  * 0.分治法
    * [0.Karatsuba乘法](classic/divide_and_conquer/Karatsuba.py)
    * [1.Strassen矩阵乘法](classic/divide_and_conquer/Strassen.py)
    * [2.棋盘覆盖问题](classic/divide_and_conquer/ChessboardCoverage.py)
    * [3.最近点对问题](classic/divide_and_conquer/ClosestPairOfPoints.py)
    * [4.循环赛日程表](classic/divide_and_conquer/RoundRobinSchedule.py)
    * [5.Hanoi塔](classic/divide_and_conquer/Hanoi.py)
  * 1.动态规划
    * [0.Fibonacci数列](classic/dynamic_programming/FibonacciSequence.py)
    * 1.背包问题
      * [0.0-1背包问题](classic/dynamic_programming/KnapsackOfZeroOne.py)
      * [1.完全背包问题](classic/dynamic_programming/KnapsackOfComplete.py)
      * [2.多重背包问题](classic/dynamic_programming/KnapsackOfMultiple.py)
    * [2.零钱兑换问题](classic/dynamic_programming/CoinChange.py)
    * [3.最长上升子序列(LIS)](classic/dynamic_programming/LongestIncreasingSubsequence.py)
    * [4.最长公共子序列(LCS)](classic/dynamic_programming/LongestCommonSubsequence.py)
    * [5.最长公共子串](classic/dynamic_programming/LongestCommonSubstring.py)
    * [6.最长回文子串](classic/dynamic_programming/LongestPalindromicSubstring.py)
    * [7.Levenshtein距离](classic/dynamic_programming/LevenshteinDistance.py)
  * 2.贪心算法
    * [0.Huffman编码](classic/greedy_algorithm/HuffmanCoding.py)
    * [1.部分背包问题](classic/greedy_algorithm/KnapsackOfFractional.py)
    * [2.活动安排问题](classic/greedy_algorithm/ActivitySelection.py)
    * [3.区间覆盖问题](classic/greedy_algorithm/IntervalCoverage.py)
  * 3.回溯法
    * 0.排列组合
      * [0.排列](classic/back_tracking/Arrangement.py)
      * [1.组合](classic/back_tracking/Combination.py)
      * [2.子集](classic/back_tracking/Subcollection.py)
    * [1.八皇后问题](classic/back_tracking/EightQueens.py)
    * [2.批处理作业调度问题](classic/back_tracking/BatchJobsScheduling.py)
    * [3.连续邮资问题](classic/back_tracking/ContinuousPostage.py)
    * [4.数独](classic/back_tracking/Sudoku.py)
  * 4.分支限界法
    * [0.最优装载问题](classic/branch_and_bound/OptimalLoading.py)
* 6.其他
  * [0.大数加减乘除](other/BigInteger.py)
  * [1.Josephus环](other/JosephusRing.py)
  * [2.逆波兰式(RPN)](other/RPN.py)
  * [3.Manacher](other/Manacher.py)
  * [4.雪花算法](other/SnowFlake.py)
  * [5.坐标系转换(WGS84&GCJ-02&BD09)](other/GPSConverter.py)