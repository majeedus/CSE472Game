using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace StepDX
{
    public class ProjectileGenerator
    {
        Texture texture;
        private Device device = null;
        float count = 0;
        public ProjectileGenerator(Device d)
        {
            device = d;
            texture = TextureLoader.FromFile(device, "../../bulletbill.png");
        }

        public List<Polygon> Advance(float dt, List<Polygon> world)
        {
            count += 1;
            if (count > 250)
            {
                 count = 0;
                Random random = new Random();
                float location =(float) (4* random.NextDouble());

                Projectile projectile = new Projectile();
                projectile.Tex = texture;
                projectile.AddVertex(new Vector2(32, location));
                projectile.AddTex(new Vector2(0,1));
                projectile.AddVertex(new Vector2(32, .25f + location));
                projectile.AddTex(new Vector2(0, 0));
                projectile.AddVertex(new Vector2(32.5f, .25f + location));
                projectile.AddTex(new Vector2(1, 0));
                projectile.AddVertex(new Vector2(32.5f, location));
                projectile.AddTex(new Vector2(1, 1));
                projectile.Color = Color.Transparent;
                projectile.Transparent = true;
                
                projectile.Speed = 20;

                
                //projectile.Tex = 
                world.Add(projectile);
            }
            List<Polygon> list = new List<Polygon>();
            foreach(Polygon p in world)
            {
                Projectile x;
                if(p.GetType() == typeof(Projectile))
                {
                    x = (Projectile)(p);
                    float z = x.GetLocation();
                    if (z < .1f && z != 0)
                    {
                        list.Add(p);
                    }
                }
               
            }
            foreach (Polygon p in list)
            {
                world.Remove(p);
            }
            return world;
        }
        
    }
}
