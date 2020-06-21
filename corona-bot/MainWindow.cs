using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Threading;
using AForge.Video;
using AForge.Video.DirectShow;
using Emgu.CV;
using Emgu.CV.Structure;

namespace corona_bot
{
    public partial class MainWindow : Form
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        FilterInfoCollection filter;
        VideoCaptureDevice device;

        SerialPort port;
        String[] ports;

        private void ButtonStart_Click(object sender, EventArgs e)
        {
            port = new SerialPort(comboBox2.Text, 9600);
            device = new VideoCaptureDevice(filter[comboBox1.SelectedIndex].MonikerString);
            device.NewFrame += DeviceNewFrame;
            device.Start();
        }

        private void DeviceNewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            Bitmap bitmap = (Bitmap)eventArgs.Frame.Clone();
            Image<Bgr, byte> grayImage = new Image<Bgr, byte>(bitmap);
            Rectangle[] rectangles = cascadeClassifier.DetectMultiScale(grayImage, 1.2, 1);
            if(rectangles.Length != 0)
            {

                Rectangle largestRect = rectangles.Aggregate((r1, r2) =>
                    (r1.Height * r1.Width) > (r2.Height * r2.Width) ? r1 : r2);

                int posX = largestRect.X;
                int posY = largestRect.Y;

                int width = largestRect.Width;
                int height = largestRect.Height;

                //i hate this bullshit LET ME EDIT LABELS ON A DIFFERENT THREAD GODAMMIT
                this.BeginInvoke((System.Windows.Forms.MethodInvoker)delegate ()
                {
                    posLabel.Text = $"X:{posX.ToString()} Y:{posY.ToString()}";
                    sizeLabel.Text = $"width:{width.ToString()} height:{height.ToString()}";
                });

                //these are placeholder numbers
                if(largestRect.X > 280)
                {
                    SendData("turnRight");
                } else if(largestRect.X < 220)
                {
                    SendData("turnLeft");
                } else
                {
                    if(largestRect.Width >= 300 && largestRect.Height >= 300)
                    {
                        SendData("kill");
                    } else
                    {
                        SendData("gamerTime");
                    }
                }

                foreach (Rectangle rectangle in rectangles)
                {
                    
                    using (Graphics graphics = Graphics.FromImage(bitmap))
                    {
                        using (Pen pen = new Pen(Color.Red, 1))
                        {
                            graphics.DrawRectangle(pen, rectangle);
                        }
                    }
                }
            } else
            {
                SendData("notSoGamerTime");
            }
            pictureBox1.Image = bitmap;
        }

        static readonly CascadeClassifier cascadeClassifier = new CascadeClassifier("haarcascade_frontalface_default.xml");

        void SendData(string data)
        {
            if(port != null)
            {
                port.Open();
                port.Write(data);
                port.Close();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            filter = new FilterInfoCollection(FilterCategory.VideoInputDevice);
            foreach (FilterInfo device in filter)
            {
                comboBox1.Items.Add(device.Name);
            }
            comboBox1.SelectedIndex = 0;
            device = new VideoCaptureDevice();
            ports = SerialPort.GetPortNames();
            comboBox2.Items.AddRange(ports);
            comboBox2.SelectedIndex = 0;
            posLabel.Text = "";
            sizeLabel.Text = "";
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            SendData("stop");
            if (device.IsRunning)
            {
                device.Stop();
            }
        }
    }
}
