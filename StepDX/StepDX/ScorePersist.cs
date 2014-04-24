using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace StepDX
{
    class ScorePersist
    {
        private string persistenceFilename;

        private XDocument scoreboard;

        public ScorePersist(string fileName)
        {
            persistenceFilename = fileName;
        }

        public void Load()
        {
            try
            {
                scoreboard = XDocument.Load(persistenceFilename);
            }
            catch
            {
                scoreboard = null;
            }
            scoreboard = scoreboard ?? new XDocument(
                new XDeclaration("1.0", "utf-8", "yes"),
                new XComment("Mario App Scoreboard Persistent Storage"),
                new XElement("scoreboard"));
        }

        public void Save()
        {
            scoreboard.Save(persistenceFilename);
        }

        public void AddScore(string name, int score)
        {
            scoreboard.Root.Add(new XElement("score",
                new XAttribute("name", name),
                new XAttribute("value", score)));
        }

        public HighScores GetHighScores()
        {
            HighScores scores = new HighScores();
            var orderedList = scoreboard.Root.Elements("score").OrderByDescending(n => int.Parse(n.Attribute("value").Value));
            foreach (var d in orderedList.Take(10))
            {
                scores.AddEntry(d.Attribute("name").Value, int.Parse(d.Attribute("value").Value));
            }
            return scores;
        }
    }
}
