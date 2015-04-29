using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace StepDX
{
    public static class ScorePrompt
    {
        public static string ShowDialog(int score)
        {
            Form prompt = new Form();
            prompt.Width = 400;
            prompt.Height = 180;
            StringBuilder builder = new StringBuilder();
            builder.AppendLine("You win!");
            builder.Append("Score: ");
            builder.Append(score);
            builder.Append("\n");
            builder.AppendLine("Your name? : ");
            prompt.Text = "Victory!";
            Label textLabel = new Label() { Left = 50, Top = 20, Height = 60, Text = builder.ToString() };
            TextBox textBox = new TextBox() { Left = 50, Top = 80, Width = 200 };
            Button confirmation = new Button() { Text = "Ok", Left = 280, Width = 80, Top = 80 };
            confirmation.Click += (sender, e) => { prompt.Close(); };
            prompt.Controls.Add(confirmation);
            prompt.Controls.Add(textLabel);
            prompt.Controls.Add(textBox);
            prompt.ShowDialog();
            return textBox.Text;
        }
    }
}
