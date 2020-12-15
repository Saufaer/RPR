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
        public Form1(int i)
        {
            InitializeComponent();
            ReadNRun(i);
        }

        public void RunProcess(string path)
        {
                if (File.Exists(path))
                {
                    // This path is a file
                    ProcessFile(path);
                }
                else if (Directory.Exists(path))
                {
                    // This path is a directory
                    ProcessDirectory(path);
                }
                else
                {
                    textBox1.Text = path+" is not a valid file or directory";
                }
        }

        // Process all files in the directory passed in, recurse on any directories
        // that are found, and process the files they contain.
        public  void ProcessDirectory(string targetDirectory)
        {
            // Process the list of files found in the directory.
            string[] fileEntries = Directory.GetFiles(targetDirectory);
            foreach (string fileName in fileEntries)
                ProcessFile(fileName);

            // Recurse into subdirectories of this directory.
            string[] subdirectoryEntries = Directory.GetDirectories(targetDirectory);
            foreach (string subdirectory in subdirectoryEntries)
                ProcessDirectory(subdirectory);
        }

        // Insert logic for processing found files here.
        public  void ProcessFile(string path)
        {
            textBox1.Text = "Processed file "+ path;
            DrawPoints(path, GetAfter(GetBefore(path, "."),"\\"), 45);
        }
        public string GetAfter(string text, string stopAt = "\\")
        {
            if (!String.IsNullOrWhiteSpace(text))
            {
                int charLocation = text.IndexOf(stopAt, StringComparison.Ordinal);

                if (charLocation > 0)
                {
                    return text.Substring(charLocation, text.Length-1);
                }
            }

            return String.Empty;
        }
        public string GetBefore(string text, string stopAt = ".")
        {
            if (!String.IsNullOrWhiteSpace(text))
            {
                int charLocation = text.IndexOf(stopAt, StringComparison.Ordinal);

                if (charLocation > 0)
                {
                    return text.Substring(0, charLocation);
                }
            }

            return String.Empty;
        }
        void ReadNRun(int i)
        {
            string path = "";
            
                while (chart1.Series.Count > 0) { chart1.Series.RemoveAt(0); }
                foreach (var series in chart1.Series)
                {
                    chart1.Series.Clear();
                    series.Points.Clear();
                }
                this.chart1.DataBind();

                path += i.ToString();
                RunProcess(path);


                path = "";

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
                    if(type == "\\Points")
                    {
                        textBox2.AppendText(line + "\r\n");
                    }

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
            if(type=="\\Points")
            {
                chart1.Series.Add(type);
                chart1.Series[type].ChartType = SeriesChartType.Point;
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
                    chart1.Series[type].Points[i].Color = Color.Red;
                    chart1.Annotations.Add(TA);
                    i++;
                }
            }
            if(type!= "\\Points")
            {
                chart1.Series.Add(type);
                chart1.Series[type].ChartType = SeriesChartType.Line;
                foreach (var pairL in listPoints)
                {
                    nameP = pairL.Key;
                    p = pairL.Value.Key;
                    u = pairL.Value.Value;
                    
                    chart1.Series[type].Points.AddXY(p, u);

                }
            }
        }
    }
}
