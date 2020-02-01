package SpiderFly06;

import com.google.gson.Gson;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.TimerTask;
import java.util.Timer;
import java.util.List;

public class Window extends JFrame {
    private final int W_WIGHT = 800;
    private final int W_HEIGHT = 800;
    private final int VERTEX_RADIUS = 30;
    private JPanel mainPanel;
    private JButton buttonStart;
    private JButton buttonStop;
    private JPanel canvasPanel;
    private JTextField vertexField;
    private JTextField edgeField;
    private JTextField flyField;
    private JButton generateButton;
    private JTextField weightField;
    private JTextField timeField;
    private JTextArea textArea;
    private Graph graph;
    private Dimension canvasSize;
    private JMenuBar menuBar = new JMenuBar();
    private SpiderMover mover;
    private Timer timer;
    private Gson gson = new Gson();
    private List<Integer> ribsPath = new ArrayList<>();

    private Window() {
        super("Spider and fly");
        $$$setupUI$$$();
        setContentPane(mainPanel);
        setVisible(true);
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        setBounds(screenSize.width / 2 - W_WIGHT / 2, screenSize.height / 2 - W_HEIGHT / 2, W_WIGHT, W_HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        createMenu();

        canvasSize = canvasPanel.getSize();

        buttonStart.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if (timer != null) {
                    timer.cancel();
                    timer.purge();
                }
                int timing;
                try {
                    timing = Integer.parseInt(timeField.getText());
                } catch (NumberFormatException err) {
                    return;
                }
                mover = new SpiderMover(timing);
                timer = new Timer();
                ribsPath = new ArrayList<>();
                graph.resetState();
                graph.getPath(timing);
                timer.schedule(mover, 0, 1000);
            }
        });

        buttonStop.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                timer.cancel();
                timer.purge();
                graph.resetSpider();
                repaint();
            }
        });

        canvasPanel.repaint();
        generateButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                ribsPath = new ArrayList<>();
                int vertexCount, edgeCount, flyCount, weightSum, timeCount;
                try {
                    vertexCount = Integer.parseInt(vertexField.getText());
                    edgeCount = Integer.parseInt(edgeField.getText());
                    flyCount = Integer.parseInt(flyField.getText());
                    weightSum = Integer.parseInt(weightField.getText());
                    timeCount = Integer.parseInt(timeField.getText());
                } catch (NumberFormatException err) {
                    JOptionPane.showMessageDialog(Window.this, "Ошибка в одном из полей ввода" +
                            "\nНе удалось преобразовать в число", "Ошибка", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                if (weightSum < edgeCount) {
                    JOptionPane.showMessageDialog(Window.this, "Сумма весов не может быть " +
                            "меньше количества ребер", "Ошибка", JOptionPane.INFORMATION_MESSAGE);
                    return;
                }
                if (vertexCount <= flyCount) {
                    JOptionPane.showMessageDialog(Window.this, "Ошибка в задании " +
                            "числа мух и вершин", "Ошибка", JOptionPane.INFORMATION_MESSAGE);
                    return;
                }
                if (timeCount > 15) {
                    JOptionPane.showMessageDialog(Window.this, "Ошибка в задании " +
                            "времени", "Ошибка", JOptionPane.INFORMATION_MESSAGE);
                    return;
                }
                if (graph == null) graph = new Graph();
                graph.generate(vertexCount, edgeCount, flyCount, weightSum);
                graph.replaceVertexes(canvasPanel.getSize(), VERTEX_RADIUS);

                textArea.setText(String.format("Осталось времени %s \n Собрано мух 0", timeField.getText()));

                repaint();
            }
        });
        super.repaint();
    }

    private void createMenu() {
        JMenu fileMenu = new JMenu("Файл");

        JMenuItem openFile = new JMenuItem("Загрузить паутину");
        openFile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser(Paths.get("").toString());
                int res = fileChooser.showDialog(Window.this, "");
                if (res == JFileChooser.APPROVE_OPTION) {
                    StringBuilder s = new StringBuilder();
                    try {
                        Files.readAllLines(Paths.get(fileChooser.getSelectedFile().getPath())).forEach(s::append);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    graph = gson.fromJson(s.toString(), Graph.class);
                    Window.this.repaint();
                }
            }
        });
        fileMenu.add(openFile);

        JMenuItem saveFile = new JMenuItem("Сохранить паутину");
        saveFile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser(Paths.get("").toString());
                int res = fileChooser.showDialog(Window.this, "");
                if (res == JFileChooser.APPROVE_OPTION)
                    try {
                        Files.write(Paths.get(fileChooser.getSelectedFile().getPath()), gson.toJson(graph, Graph.class).getBytes());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
            }
        });
        fileMenu.add(saveFile);

        JMenu HelpMenu = new JMenu("Помощь");

        JMenuItem HelpMenuItem = new JMenuItem("Помощь");
        HelpMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JOptionPane.showMessageDialog(Window.this, "М8О-312Б  -  Горшков Д.С. \n" +
                        "6 лаба - паук и мухи", "Помощь", JOptionPane.INFORMATION_MESSAGE);
            }
        });
        HelpMenu.add(HelpMenuItem);

        JMenu settingMenu = new JMenu("Конфигурация");

        JMenuItem loadConfiguration = new JMenuItem("Загрузить");
        loadConfiguration.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                int res = fileChooser.showDialog(Window.this, "");
                if (res == JFileChooser.APPROVE_OPTION) {
                    String path = fileChooser.getSelectedFile().getPath();
                    StringBuilder s = new StringBuilder();
                    try {
                        Files.readAllLines(Paths.get(path)).forEach(s::append);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    Settings settings = gson.fromJson(s.toString(), Settings.class);

                    vertexField.setText(Integer.toString(settings.getVertexCount()));
                    edgeField.setText(Integer.toString(settings.getEdgeCount()));
                    flyField.setText(Integer.toString(settings.getFlyCount()));
                    weightField.setText(Integer.toString(settings.getSumWeight()));
                    timeField.setText(Integer.toString(settings.getTiming()));
                }
            }
        });
        settingMenu.add(loadConfiguration);

        JMenuItem saveConfiguration = new JMenuItem("Сохранить");
        saveConfiguration.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                Settings settings = new Settings();
                int vertexCount, edgeCount, flyCount, weightSum, timing;
                try {
                    vertexCount = Integer.parseInt(vertexField.getText());
                    edgeCount = Integer.parseInt(edgeField.getText());
                    flyCount = Integer.parseInt(flyField.getText());
                    weightSum = Integer.parseInt(weightField.getText());
                } catch (NumberFormatException err) {
                    JOptionPane.showMessageDialog(Window.this, "Ошибка в одном из полей ввода" +
                            "\nНе удалось преобразовать в число", "Ошибка", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                settings.setVertexCount(vertexCount);
                settings.setEdgeCount(edgeCount);
                settings.setFlyCount(flyCount);
                settings.setSumWeight(weightSum);

                try {
                    timing = Integer.parseInt(timeField.getText());
                    settings.setTiming(timing);
                } catch (NumberFormatException ignored) {
                }

                JFileChooser fileChooser = new JFileChooser();
                int res = fileChooser.showDialog(Window.this, "");
                if (res == JFileChooser.APPROVE_OPTION) {
                    try {
                        Files.write(Paths.get(fileChooser.getSelectedFile().getPath()), gson.toJson(settings, Settings.class).getBytes());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        settingMenu.add(saveConfiguration);

        menuBar.add(fileMenu);
        menuBar.add(settingMenu);
        menuBar.add(HelpMenu);
        setJMenuBar(menuBar);
    }

    public static void main(String[] args) {
        Window w = new Window();
    }

    private void createUIComponents() {
        canvasPanel = new JPanel() {
            @Override
            public void paint(Graphics g) {
                super.paint(g);

                if (graph == null) return;
                Dimension size = getSize();
                if (!size.equals(canvasSize)) {
                    // setting new X and Y if window was resized
                    graph.replaceVertexes(size, VERTEX_RADIUS);
                    canvasSize = size;
                }

                // for drawing graph as a circle need to choose min size edge of window
                // as a radius of circle for it will see all
                int r = Integer.min(size.height, size.width) / 2 - 2 * VERTEX_RADIUS;
                if (r < VERTEX_RADIUS)
                    return;

                if (!graph.isEmpty()) {
                    int[][] matrix = graph.getMatrix();
                    for (int i = 0; i < matrix.length; i++) {
                        for (int j = 0; j < i; j++) {
                            if (matrix[i][j] > 0) {
                                for (int k = 0; k < ribsPath.size() - 1; k++) {
                                    if (ribsPath.get(k) == i && ribsPath.get(k + 1) == j) {
                                        g.setColor(Color.ORANGE);
                                        break;
                                    }
                                    if (ribsPath.get(k) == j && ribsPath.get(k + 1) == i) {
                                        g.setColor(Color.ORANGE);
                                        break;
                                    }
                                }
                                Vertex v1 = graph.getVertex(i), v2 = graph.getVertex(j);
                                g.drawLine(v1.getX() + VERTEX_RADIUS / 2, v1.getY() + VERTEX_RADIUS / 2,
                                        v2.getX() + VERTEX_RADIUS / 2, v2.getY() + VERTEX_RADIUS / 2);
                                g.setColor(Color.BLACK);
                                g.drawString(Integer.toString(matrix[i][j]), Math.abs(v1.getX() + v2.getX()) / 2,
                                        Math.abs(v1.getY() + v2.getY()) / 2);
                            }
                        }
                    }

                    for (int i = 0; i < graph.size(); ++i) {
                        Vertex v = graph.getVertex(i);
                        switch (v.getState()) {
                            case Empty:
                            case Spider:
                                g.setColor(Color.BLACK);
                                break;
                            case Fly:
                                g.setColor(Color.GRAY);
                                break;
                            case Visited:
                            case FlyGot:
                                g.setColor(Color.LIGHT_GRAY);
                        }
                        g.fillOval(v.getX(), v.getY(), VERTEX_RADIUS, VERTEX_RADIUS);
                        g.setColor(Color.WHITE);
                        g.drawString(Integer.toString(i), v.getX() + VERTEX_RADIUS / 2, v.getY() + VERTEX_RADIUS / 2);
                    }

                    g.setColor(Color.RED);
                    g.fillOval(graph.getSpiderX() + VERTEX_RADIUS / 4, graph.getSpiderY() + VERTEX_RADIUS / 4,
                            VERTEX_RADIUS / 2, VERTEX_RADIUS / 2);
                }
            }
        };
    }

    /**
     * Method generated by IntelliJ IDEA GUI Designer
     * >>> IMPORTANT!! <<<
     * DO NOT edit this method OR call it in your code!
     *
     * @noinspection ALL
     */
    private void $$$setupUI$$$() {
        createUIComponents();
        mainPanel = new JPanel();
        mainPanel.setLayout(new com.intellij.uiDesigner.core.GridLayoutManager(13, 2, new Insets(5, 5, 5, 5), -1, -1));
        final JPanel panel1 = new JPanel();
        panel1.setLayout(new com.intellij.uiDesigner.core.GridLayoutManager(1, 3, new Insets(0, 0, 0, 0), -1, -1));
        mainPanel.add(panel1, new com.intellij.uiDesigner.core.GridConstraints(12, 0, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_CENTER, com.intellij.uiDesigner.core.GridConstraints.FILL_BOTH, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_SHRINK | com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_SHRINK | com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_GROW, null, new Dimension(585, 34), null, 0, true));
        buttonStart = new JButton();
        buttonStart.setText("Старт");
        panel1.add(buttonStart, new com.intellij.uiDesigner.core.GridConstraints(0, 0, 1, 2, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_CENTER, com.intellij.uiDesigner.core.GridConstraints.FILL_HORIZONTAL, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_SHRINK | com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
        buttonStop = new JButton();
        buttonStop.setText("Стоп");
        panel1.add(buttonStop, new com.intellij.uiDesigner.core.GridConstraints(0, 2, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_CENTER, com.intellij.uiDesigner.core.GridConstraints.FILL_HORIZONTAL, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_SHRINK | com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
        mainPanel.add(canvasPanel, new com.intellij.uiDesigner.core.GridConstraints(0, 0, 12, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_CENTER, com.intellij.uiDesigner.core.GridConstraints.FILL_BOTH, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_SHRINK | com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_WANT_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_SHRINK | com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_GROW, null, new Dimension(585, 24), null, 0, false));
        final JLabel label1 = new JLabel();
        label1.setText("Количество вершин");
        mainPanel.add(label1, new com.intellij.uiDesigner.core.GridConstraints(0, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_NONE, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
        final JLabel label2 = new JLabel();
        label2.setText("Количество ребер");
        mainPanel.add(label2, new com.intellij.uiDesigner.core.GridConstraints(2, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_NONE, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
        final JLabel label3 = new JLabel();
        label3.setText("Количество мух");
        mainPanel.add(label3, new com.intellij.uiDesigner.core.GridConstraints(4, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_NONE, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
        edgeField = new JTextField();
        mainPanel.add(edgeField, new com.intellij.uiDesigner.core.GridConstraints(3, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_HORIZONTAL, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_WANT_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, new Dimension(100, -1), null, 0, false));
        flyField = new JTextField();
        flyField.setText("");
        mainPanel.add(flyField, new com.intellij.uiDesigner.core.GridConstraints(5, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_HORIZONTAL, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_WANT_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, new Dimension(100, -1), null, 0, false));
        final com.intellij.uiDesigner.core.Spacer spacer1 = new com.intellij.uiDesigner.core.Spacer();
        mainPanel.add(spacer1, new com.intellij.uiDesigner.core.GridConstraints(11, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_CENTER, com.intellij.uiDesigner.core.GridConstraints.FILL_VERTICAL, 1, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_WANT_GROW, null, null, null, 0, false));
        vertexField = new JTextField();
        mainPanel.add(vertexField, new com.intellij.uiDesigner.core.GridConstraints(1, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_HORIZONTAL, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, new Dimension(100, -1), null, 0, false));
        final JLabel label4 = new JLabel();
        label4.setText("Максимальная сумма весов ребер");
        mainPanel.add(label4, new com.intellij.uiDesigner.core.GridConstraints(6, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_NONE, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
        generateButton = new JButton();
        generateButton.setText("Сгенерировать");
        mainPanel.add(generateButton, new com.intellij.uiDesigner.core.GridConstraints(12, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_CENTER, com.intellij.uiDesigner.core.GridConstraints.FILL_HORIZONTAL, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_SHRINK | com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_CAN_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
        weightField = new JTextField();
        mainPanel.add(weightField, new com.intellij.uiDesigner.core.GridConstraints(7, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_HORIZONTAL, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_WANT_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, new Dimension(150, -1), null, 0, false));
        final JLabel label5 = new JLabel();
        label5.setText("Время");
        mainPanel.add(label5, new com.intellij.uiDesigner.core.GridConstraints(8, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_NONE, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
        timeField = new JTextField();
        mainPanel.add(timeField, new com.intellij.uiDesigner.core.GridConstraints(9, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_WEST, com.intellij.uiDesigner.core.GridConstraints.FILL_HORIZONTAL, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_WANT_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_FIXED, null, new Dimension(150, -1), null, 0, false));
        textArea = new JTextArea();
        textArea.setText("");
        mainPanel.add(textArea, new com.intellij.uiDesigner.core.GridConstraints(10, 1, 1, 1, com.intellij.uiDesigner.core.GridConstraints.ANCHOR_CENTER, com.intellij.uiDesigner.core.GridConstraints.FILL_BOTH, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_WANT_GROW, com.intellij.uiDesigner.core.GridConstraints.SIZEPOLICY_WANT_GROW, null, new Dimension(150, 50), null, 0, false));
    }

    /**
     * @noinspection ALL
     */
    public JComponent $$$getRootComponent$$$() {
        return mainPanel;
    }

    private class SpiderMover extends TimerTask {
        int timing;
        int flyCount = 0;

        SpiderMover(int timing) {
            this.timing = timing;
        }

        @Override
        public void run() {
            if (graph == null) {
                timer.cancel();
                return;
            }
            repaint();

            if (graph.isGetFly())
                flyCount++;

            ribsPath.add(graph.getSpiderIndex());

            int weight = graph.moveSpider();
            timing -= weight;

            textArea.setText(String.format("Осталось времени %d \nСобрано мух %d", timing, flyCount));

            if (weight < 0) {
                timer.cancel();
                timer.purge();
                graph.resetSpider();
            }
        }
    }
}
