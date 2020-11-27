using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Windows.Forms.DataVisualization;
using System.Windows.Forms.DataVisualization.Charting;

namespace RPR_Graph
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            DrawPoints(@"Points.txt","Points",45);
            DrawPoints(@"cl2_1.txt", "cl2_1", 15);
            DrawPoints(@"L2_1.txt", "L2_1", 30);
            DrawPoints(@"L1_1.txt", "L1_1", 30);
        }
        void DrawPoints(string file, string type, int color)
        {
            string path = file;
            string line = "";

            var list = new List<KeyValuePair<string, double>>();
            double doubleVal;
            char[] charSeparators = new char[] { '=' };
            using (StreamReader sr = new StreamReader(path))
            {
                while (sr.Peek() >= 0)
                {
                    line = sr.ReadLine();

                    string[] words = line.Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
                    if(words.Length==2)
                    {
                        if (Double.TryParse(words[1], out doubleVal))
                        {
                            list.Add(new KeyValuePair<string, double>(words[0], doubleVal));
                        }

                    }

                }
            }
            var listPoints = new List<KeyValuePair<string, KeyValuePair<double, double>>>();
            string name="";
            double value = -1;
            foreach (var pair in list)
            {
                if(pair.Key.Split('.')[0] == name)
                {
                    listPoints.Add(new KeyValuePair<string, KeyValuePair<double, double>>(pair.Key.Split('.')[0], new KeyValuePair<double, double>(value, pair.Value)));
                    name = "";
                    value = -1;
                }
                else
                {
                    name = pair.Key.Split('.')[0];
                    value = pair.Value;
                }
            }

            string nameP = "";
            double p = -1;
            double u = -1;
            int i = 0;
            if(type=="Points")
            {
                foreach (var pairL in listPoints)
                {
                    nameP = pairL.Key;
                    p = pairL.Value.Key;
                    u = pairL.Value.Value;
                    textBox1.AppendText(nameP + " = " + p + " ; " + u + "\r\n");

                    chart1.Series[type].Points.AddXY(p, u);
                    TextAnnotation TA = new TextAnnotation();
                    TA.Text = nameP;
                    TA.SetAnchor(chart1.Series[type].Points[i]);
                    chart1.Series[type].Points[i].Color = Color.HotPink;
                    chart1.Annotations.Add(TA);
                    i++;
                }
            }
            if(type!= "Points")
            {
                chart1.Series[type].ChartType = SeriesChartType.Line;
               // chart1.Series[type].Color = Color.FromArgb(color, color, color);
                foreach (var pairL in listPoints)
                {
                    nameP = pairL.Key;
                    p = pairL.Value.Key;
                    u = pairL.Value.Value;
                    // textBox1.AppendText(nameP + " = " + p + " ; " + u + "\r\n");
                    
                    chart1.Series[type].Points.AddXY(p, u);
                   // TextAnnotation TA = new TextAnnotation();
                   // TA.Text = nameP;
                   // TA.SetAnchor(chart1.Series[type].Points[i]);
                    chart1.Series[type].Points[i].Color = Color.HotPink;
                }
            }
        }
    }
}
