using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StepDX
{
    class HighScores
    {
        private List<KeyValuePair<string, int>> entries;

        public HighScores()
        {
            entries = new List<KeyValuePair<string, int>>();
        }

        public void AddEntry(string name, int score)
        {
            entries.Add(new KeyValuePair<string, int>(name, score));
        }

        public string GenerateScoreCard()
        {
            StringBuilder builder = new StringBuilder();
            builder.AppendLine("Name \t Score");
            builder.AppendLine("-------------");
            foreach (var p in entries)
            {
                builder.Append(p.Key);
                builder.Append("\t");
                builder.Append(p.Value);
                builder.Append("\n");
            }
            return builder.ToString();
        }
    }
}
