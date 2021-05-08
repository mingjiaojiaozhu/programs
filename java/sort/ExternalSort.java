package sort;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

public class ExternalSort {
    public void sort(String inFile, String outFile) throws IOException {
        int count = readFile(inFile);
        mergeTempFiles(inFile, outFile, count);
        for (int i = 0; i < count; ++i) {
            new File(inFile + "-" + i).delete();
        }
    }

    private int readFile(String inFile) throws IOException {
        List<Integer> values = new ArrayList<>();
        int count = 0;

        try(BufferedReader handle = new BufferedReader(new InputStreamReader(new FileInputStream(inFile)))) {
            String line = "";
            while (null != (line = handle.readLine())) {
                values.add(Integer.parseInt(line));
                if (values.size() >= 65536) {
                    writeTempFiles(values, inFile, count);
                    ++count;
                }
            }
        }

        if (!values.isEmpty()) {
            writeTempFiles(values, inFile, count);
            ++count;
        }
        return count;
    }

    private void mergeTempFiles(String inFile, String outFile, int count) throws IOException {
        Queue<HeapNode> queue = new PriorityQueue<>(cmp);
        for (int i = 0; i < count; ++i) {
            queue.offer(new HeapNode(inFile, i));
        }

        try(BufferedWriter handle = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outFile, false)))) {
            while (!queue.isEmpty()) {
                HeapNode heap = queue.poll();
                handle.write(heap.value + "\n");

                String line = heap.handle.readLine();
                if (null == line) {
                    heap.handle.close();
                } else {
                    heap.value = Integer.parseInt(line);
                    queue.offer(heap);
                }
            }
        }
    }

    private void writeTempFiles(List<Integer> values, String inFile, int index) throws IOException {
        Collections.sort(values);

        try(BufferedWriter handle = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(inFile + "-" + index, false)))) {
            for (int value : values) {
                handle.write(value + "\n");
            }
        }
        values.clear();
    }

    private class HeapNode {
        public int value = 0;
        public BufferedReader handle = null;

        public HeapNode(String inFile, int index) throws IOException {
            handle = new BufferedReader(new InputStreamReader(new FileInputStream(inFile + "-" + index)));
            value = Integer.parseInt(handle.readLine());
        }
    }

    private static Comparator<HeapNode> cmp = new Comparator<HeapNode>() {
        @Override
        public int compare(HeapNode node1, HeapNode node2) {
            return node1.value - node2.value;
        }
    };
}
