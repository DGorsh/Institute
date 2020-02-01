package SpiderFly06;

import java.awt.*;
import java.util.*;
import java.util.List;

public class Graph {
    private Map<Integer, Map<Integer, Integer>> adjacencyList = new Hashtable<>();
    private Map<Integer, Vertex> vertexMap = new Hashtable<>();
    private int counter = 0;
    private int spiderIndex;
    private int bestFly;
    private int bestTime;
    private List<Integer> path = new ArrayList<>();
    private Vertex spider;

    public void generate(int vertexCount, int edgeCount, int flyCount, int sumWeight){
        adjacencyList.clear();
        vertexMap.clear();
        path.clear();
        counter = 0;
        spiderIndex = 0;
        bestTime = 0;
        bestFly = 0;
        spider = null;

        for (int i = 0; i < vertexCount; i++) {
            addVertex();
        }
        int edgeAdded = 0, addedWeight = 0, meanWeight = sumWeight / edgeCount;
        Random r = new Random();
        int maxEdge = Integer.min(edgeCount, vertexCount*(vertexCount-1) / 2);
        while (edgeAdded < maxEdge){
            int i = r.nextInt(vertexCount), j = r.nextInt(vertexCount);
            if (edgeAdded != 0 && adjacencyList.get(i).isEmpty()) continue;
            if (i == j) continue;
            if (adjacencyList.get(i) != null && adjacencyList.get(i).get(j) == null) {
                int w = meanWeight == 1 ? 1 : r.nextInt(meanWeight) + 1;
                if (addedWeight + w > sumWeight) continue;
                addEdge(i, j, w);
                addedWeight += w;
                edgeAdded++;
            }
        }

        int addedFly = 0;
        while (addedFly < flyCount && addedFly <= vertexCount - 1 && flyCount <= edgeCount){
            int index = r.nextInt(vertexCount);
            while (adjacencyList.get(index).isEmpty() || getVertex(index).getState() == State.Fly)
                index = r.nextInt(vertexCount);
            getVertex(index).setState(State.Fly);
            addedFly++;
        }

        boolean isSetSpider = false;
        while (!isSetSpider){
            int index = r.nextInt(vertexCount);
            if (getVertex(index).getState() == State.Empty && !adjacencyList.get(index).isEmpty()) {
                getVertex(index).setState(State.Spider);
                isSetSpider = true;
                spiderIndex = index;
                spider = getVertex(index);
            }
        }
    }

    public void addVertex(){;
        adjacencyList.put(counter, new Hashtable<>());
        vertexMap.put(counter, new Vertex());
        ++counter;
    }

    public Vertex getVertex(int index){
        return vertexMap.get(index);
    }

    public void addEdge(int vertexFrom, int vertexTo, int weight){
        adjacencyList.get(vertexFrom).put(vertexTo, weight);
        adjacencyList.get(vertexTo).put(vertexFrom, weight);
    }

    public int[][] getMatrix(){
        int size = vertexMap.size();
        int[][] matrix = new int[size][size];

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (adjacencyList.get(i).get(j) == null){
                    matrix[i][j] = 0;
                    matrix[j][i] = 0;
                }
                else {
                    matrix[i][j] = adjacencyList.get(i).get(j);
                }
            }
        }
        return matrix;
    }

    public int size() {
        return vertexMap.size();
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public void replaceVertexes(Dimension size, int VERTEX_RADIUS) {
        int r = Integer.min(size.height, size.width) / 2 - 2 * VERTEX_RADIUS;
        int i = 0;
        for (float deg = 0; deg < 2*Math.PI && i < size(); deg += 2*Math.PI / size(), ++i) {
            int x = (int) (r * Math.cos(deg)) + size.width / 2;
            int y = (int) (r * Math.sin(deg)) + size.height / 2;
            Vertex v = getVertex(i);
            v.setX(x);
            v.setY(y);
        }
        if (spider.getX() == 0 && spider.getY() == 0)
            spider = getVertex(spiderIndex);
    }

    public List<Integer> getPath(int timing){
        path.clear();
        bestFly = 0;
        bestTime = 0;
        findPath(new ArrayList<>(), new ArrayList<>(), 0, 0, timing);
        System.out.println(path);
        return path;
    }

    private void findPath(List<Integer> f_path, List<Integer> visited, int flyGot, int timing, int maxTiming) {
        if (timing > maxTiming) return;
        int index;
        if (f_path.isEmpty()) {
            index = spiderIndex;
            f_path.add(index);
        }
        else
            index = f_path.get(f_path.size() - 1);
        visited.add(index);

        if (getVertex(index).getState() == State.Fly) {
            flyGot = countFly(f_path);
        }

        if (flyGot > bestFly || (timing < bestTime && flyGot >= bestFly)){
            bestFly = flyGot;
            bestTime = timing;
            path = new ArrayList<>(f_path);
        }

        for (var entry : adjacencyList.get(index).entrySet()) {
            f_path.add(entry.getKey());
            findPath(f_path, new ArrayList<>(visited), flyGot, timing + entry.getValue(), maxTiming);
            f_path.remove(f_path.size() - 1);
//            if (!visited.contains(entry.getKey()) && entry.getValue() + timing <= maxTiming) {
//                List<Integer> newPath = new ArrayList<>(path);
//                newPath.add(entry.getKey());
//                findPath(newPath, new ArrayList<>(visited), flyGot, timing + entry.getValue(), maxTiming);
//            }
        }
    }

    private int countFly(List<Integer> path) {
        int counter = 0;
        Set<Integer> set = new HashSet<Integer>();
        for (Integer index : path) {
            set.add(index);
        }
        for (Integer index : set) {
            if (getVertex(index).getState() == State.Fly) counter += 1;
        }
        return counter;
    }

    public int getSpiderX() {
        return spider.getX();
    }

    public int getSpiderY() {
        return spider.getY();
    }

    public void resetState() {
        for (Vertex v : vertexMap.values()) {
            switch (v.getState()) {
                case FlyGot:
                    v.setState(State.Fly);
                    break;
                case Visited:
                    v.setState(State.Empty);
            }
        }
    }

    public int moveSpider() {
        if (spider.getX() == 0 && spider.getY() == 0){
            if (!path.isEmpty())
                spider = getVertex(path.get(0));
            return 0;
        }
        List<Vertex> vertexPath = getVertexList(path);
        for (int i = 0; i < vertexPath.size() - 1; i++) {
            if (spider.equals(vertexPath.get(i))){
                spider = vertexPath.get(i+1);
                if (getVertex(path.get(0)).getState() == State.Fly)
                    getVertex(path.get(0)).setState(State.FlyGot);
                else
                    getVertex(path.get(0)).setState(State.Visited);
                path.remove(0);
                try {
                    return adjacencyList.get(path.get(i)).get(path.get(i + 1));
                } catch (IndexOutOfBoundsException e) {
                    return 0;
                }
            }
        }
        return -1;
    }

    private List<Vertex> getVertexList(List<Integer> indexes) {
        List<Vertex> list = new ArrayList<>(indexes.size());
        indexes.forEach(index -> list.add(getVertex(index)));
        return list;
    }

    public void resetSpider() {
        spider = getVertex(spiderIndex);
    }

    public boolean isGetFly() {
        return spider.getState() == State.Fly;
    }

    public int getSpiderIndex() {
        for (var entry : vertexMap.entrySet()) {
            if (entry.getValue().equals(spider))
                return entry.getKey();
        }
        return -1;
    }
}