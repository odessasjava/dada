#include "dada/gl/GL.h"
#include "dada/app/Application.h"
#include "dada/gl/EBO.h"
#include "dada/gl/Program.h"
#include "dada/gl/Shader.h"
#include "dada/gl/VAO.h"
#include "dada/gl/VBO.h"

#include "dada/geometry/Transform3f.h"
#include "dada/geometry/Matrix4fUtils.h"
#include "dada/geometry/Vector3fUtils.h"

#include <vector>

//#include <cmath>

using namespace dada;

class AttributeBinder
{
public:
  typedef unsigned int index_t;
  
  static const index_t INVALID_INDEX = static_cast<index_t>(-1);
  
  struct Description
  {
    index_t index;
    int size;
    int type;
    bool normalized;
    unsigned int stride;
    const void* pointer;
  };
  
  virtual void bind() = 0;
};

class AttributeBinderVAO : public AttributeBinder
{
public:
  AttributeBinderVAO() :
    AttributeBinder(),
    m_vao()
  {
  }
  // Too complex. Refactor to autoselect between VAO or not
  AttributeBinderVAO(unsigned int count, const Description* descriptions, VBO** vbos, EBO* ebo = nullptr) :
    AttributeBinder(),
    m_vao()
  {
    init(count, descriptions, vbos, ebo);
  }
  
  void init(unsigned int count, const Description* descriptions, VBO** vbos, EBO* ebo = nullptr)
  {
    m_vao.bind();
    if (descriptions != nullptr && vbos != nullptr)
    {
      for (unsigned int i = 0; i < count; ++i)
      {
        if (vbos[i] != nullptr)
        {
          vbos[i]->bind();
        }
        auto& desc = descriptions[i];
        glEnableVertexAttribArray(desc.index);
        glVertexAttribPointer(desc.index, desc.size, desc.type, desc.normalized, desc.stride, nullptr);
      }
    }
    if (ebo != nullptr)
    {
      ebo->bind();
    }
  }
  
   virtual void bind() override
   {
     m_vao.bind();
   }

private:
  // array of ptrs to VBOs and EBO to manage them
  VAO m_vao;
};

class Geometry
{
public:
   enum AttributeType
   {
      VERTEX,
      COLOR,
      TEX_COORD,
      NORMAL
   };

   Transform3f m_transform;

   Geometry() :
      m_transform (1.0f)
   {
   }


   virtual void setAttributeLocation(AttributeType type, Program::index_t location)
   {
      
   }

   virtual void bindAttributes()
   {
   }

   virtual void drawCall()
   {
   
   }

};

class GeometryBoxColor : public Geometry
{
public:
   Program::index_t m_vertices_loc;
   Program::index_t m_colors_loc;
   VBO m_vbo_vertices;
   VBO m_vbo_colors;
   EBO m_ebo;
   VAO m_vao; // <--- Create some universal AttributeBinder (use VAO if available)

   GeometryBoxColor() :
      Geometry (),
      m_vertices_loc (Program::INVALID_INDEX),
      m_colors_loc (Program::INVALID_INDEX),
      m_vbo_vertices (),
      m_vbo_colors (),
      m_ebo (),
      m_vao ()
   {
      float vertices[8 * 3] =
      {
         -0.5f,  0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f, -0.5f,  0.5f
      };
      const dada::uint8_t colors[8 * 3] =
      {
         255,   0,   0,
           0, 255,   0,
           0,   0, 255,
           0,   0,   0,
         255, 255,   0,
         255, 255, 255,
           0, 255, 255,
         255,   0, 255
      };
      unsigned char indices[19] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1,   1, 7, 3, 5,   5,   6, 4, 0, 2 };

      m_vbo_vertices.load(sizeof(vertices), vertices);
      m_vbo_colors.load(sizeof(colors), colors);
      m_ebo.load(sizeof(indices), indices);
      
      m_vao.bind();

      //m_vbo_vertices.load(sizeof(vertices), vertices);
      m_vbo_vertices.bind();
      glEnableVertexAttribArray(/*m_vertices_loc*/ 0);
      glVertexAttribPointer(/*m_vertices_loc*/ 0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

      //m_vbo_colors.load(sizeof(colors), colors);
      m_vbo_colors.bind();
      glEnableVertexAttribArray(/*m_colors_loc*/ 1);
      glVertexAttribPointer(/*m_colors_loc*/ 1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);

      //m_ebo.load(sizeof(indices), indices);
      m_ebo.bind();
   }

   virtual void setAttributeLocation(AttributeType type, Program::index_t location) override
   {
      
   }

   virtual void bindAttributes() override
   {
      m_vao.bind();
   }

   virtual void drawCall() override
   {
      glDrawElements(GL_TRIANGLE_STRIP, 19, GL_UNSIGNED_BYTE, NULL);
   }
};

class GeometryBoxColorIndirect : public Geometry
{
public:
   Program::index_t m_vertices_loc;
   Program::index_t m_colors_loc;
   
   GeometryBoxColorIndirect() :
      Geometry (),
      m_vertices_loc (Program::INVALID_INDEX),
      m_colors_loc (Program::INVALID_INDEX)
   {
   }

   virtual void setAttributeLocation(AttributeType type, Program::index_t location) override
   {
      switch (type)
      {
         case VERTEX: m_vertices_loc = location; break;
         case COLOR:  m_colors_loc = location;   break;
      }
   }

   virtual void bindAttributes() override
   {
       static const float vertices[8 * 3] = // static to keep array after function ends
      {
         -0.5f,  0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f, -0.5f,  0.5f
      };
      static const dada::uint8_t colors[8 * 3] = // static to keep array after function ends
      {
         255,   0,   0,
           0, 255,   0,
           0,   0, 255,
           0,   0,   0,
         255, 255,   0,
         255, 255, 255,
           0, 255, 255,
         255,   0, 255
      };
       
      glEnableVertexAttribArray(m_vertices_loc);
      glVertexAttribPointer(m_vertices_loc, 3, GL_FLOAT, GL_FALSE, 0, vertices);
       
      glEnableVertexAttribArray(m_colors_loc);
      glVertexAttribPointer(m_colors_loc, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);
       
   }

   virtual void drawCall() override
   {
      unsigned char indices[19] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1,   1, 7, 3, 5,   5,   6, 4, 0, 2 };

      glDrawElements(GL_TRIANGLE_STRIP, 19, GL_UNSIGNED_BYTE, indices);
   }
};

class GeometryBoxColorVBO : public Geometry
{
public:
   Program::index_t m_vertices_loc;
   Program::index_t m_colors_loc;
   VBO m_vbo_vertices;
   VBO m_vbo_colors;
   EBO m_ebo;

   GeometryBoxColorVBO() :
      Geometry (),
      m_vertices_loc (Program::INVALID_INDEX),
      m_colors_loc (Program::INVALID_INDEX),
      m_vbo_vertices (),
      m_vbo_colors (),
      m_ebo ()
   {
      float vertices[8 * 3] =
      {
         -0.5f,  0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f, -0.5f,  0.5f
      };
      const dada::uint8_t colors[8 * 3] =
      {
         255,   0,   0,
           0, 255,   0,
           0,   0, 255,
           0,   0,   0,
         255, 255,   0,
         255, 255, 255,
           0, 255, 255,
         255,   0, 255
      };
      unsigned char indices[19] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1,   1, 7, 3, 5,   5,   6, 4, 0, 2 };

      m_vbo_vertices.load(sizeof(vertices), vertices);
      m_vbo_colors.load(sizeof(colors), colors);
      m_ebo.load(sizeof(indices), indices);
   }

   virtual void setAttributeLocation(AttributeType type, Program::index_t location) override
   {
      switch (type)
      {
         case VERTEX: m_vertices_loc = location; break;
         case COLOR:  m_colors_loc = location;   break;
      }
   }

   virtual void bindAttributes() override
   {
      glEnableVertexAttribArray(m_vertices_loc);
      m_vbo_vertices.bind();
      glVertexAttribPointer(m_vertices_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
       
      glEnableVertexAttribArray(m_colors_loc);
      m_vbo_colors.bind();
      glVertexAttribPointer(m_colors_loc, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);
       
   }

   virtual void drawCall() override
   {
      //const unsigned char indices[19] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1,   1, 7, 3, 5,   5,   6, 4, 0, 2 };
      //glDrawElements(GL_TRIANGLE_STRIP, 19, GL_UNSIGNED_BYTE, indices);

      m_ebo.bind();
      glDrawElements(GL_TRIANGLE_STRIP, 19, GL_UNSIGNED_BYTE, NULL);
   }
};

class GeometryBoxColorVAO : public Geometry
{
public:
   Program::index_t m_vertices_loc;
   Program::index_t m_colors_loc;
   VBO m_vbo_vertices;
   VBO m_vbo_colors;
   EBO m_ebo;
   VAO m_vao;

   GeometryBoxColorVAO() :
      Geometry (),
      m_vertices_loc (Program::INVALID_INDEX),
      m_colors_loc (Program::INVALID_INDEX),
      m_vbo_vertices (),
      m_vbo_colors (),
      m_ebo (),
      m_vao ()
   {
      float vertices[8 * 3] =
      {
         -0.5f,  0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f, -0.5f,  0.5f
      };
      const dada::uint8_t colors[8 * 3] =
      {
         255,   0,   0,
           0, 255,   0,
           0,   0, 255,
           0,   0,   0,
         255, 255,   0,
         255, 255, 255,
           0, 255, 255,
         255,   0, 255
      };
      unsigned char indices[19] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1,   1, 7, 3, 5,   5,   6, 4, 0, 2 };

      m_vbo_vertices.load(sizeof(vertices), vertices);
      m_vbo_colors.load(sizeof(colors), colors);
      m_ebo.load(sizeof(indices), indices);
      
      m_vao.bind();

      //m_vbo_vertices.load(sizeof(vertices), vertices);
      m_vbo_vertices.bind();
      glEnableVertexAttribArray(/*m_vertices_loc*/ 0);
      glVertexAttribPointer(/*m_vertices_loc*/ 0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

      //m_vbo_colors.load(sizeof(colors), colors);
      m_vbo_colors.bind();
      glEnableVertexAttribArray(/*m_colors_loc*/ 1);
      glVertexAttribPointer(/*m_colors_loc*/ 1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);

      //m_ebo.load(sizeof(indices), indices);
      m_ebo.bind();
   }

   virtual void setAttributeLocation(AttributeType type, Program::index_t location) override
   {
      
   }

   virtual void bindAttributes() override
   {
      m_vao.bind();
   }

   virtual void drawCall() override
   {
      glDrawElements(GL_TRIANGLE_STRIP, 19, GL_UNSIGNED_BYTE, NULL);
   }
};

/*class GeneratorBox
{
public:
   Geometry* m_geometry;

   
   GeneratorBox(Geometry& geometry) :
      m_geometry (&geometry)
   {
   }

   void generateVertices()
   {
      m_geometry->m_vertices.reserve(8 * 3);
      m_geometry->m_vertices.push_back(-0.5f); m_geometry->m_vertices.push_back(0.5f);  m_geometry->m_vertices.push_back(-0.5f);
      m_geometry->m_vertices.push_back(-0.5f); m_geometry->m_vertices.push_back(-0.5f); m_geometry->m_vertices.push_back(-0.5f);
      m_geometry->m_vertices.push_back(0.5f);  m_geometry->m_vertices.push_back(0.5f);  m_geometry->m_vertices.push_back(-0.5f);
      m_geometry->m_vertices.push_back(0.5f);  m_geometry->m_vertices.push_back(-0.5f); m_geometry->m_vertices.push_back(-0.5f);
      m_geometry->m_vertices.push_back(0.5f);  m_geometry->m_vertices.push_back(0.5f);  m_geometry->m_vertices.push_back(0.5f);
      m_geometry->m_vertices.push_back(0.5f);  m_geometry->m_vertices.push_back(-0.5f); m_geometry->m_vertices.push_back(0.5f);
      m_geometry->m_vertices.push_back(-0.5f); m_geometry->m_vertices.push_back(0.5f);  m_geometry->m_vertices.push_back(0.5f);
      m_geometry->m_vertices.push_back(-0.5f); m_geometry->m_vertices.push_back(-0.5f); m_geometry->m_vertices.push_back(0.5f);
   }
};*/


class DrawContext
{
public:
   Matrix4f m_model_view;
   Matrix4f m_projection;
};

class Effect;

class Material
{
public:
   Effect* m_effect;
};

class Effect
{
public:
   virtual void draw(DrawContext& context, Geometry& geometry, Material& material) = 0;
};

class EffectColored : public Effect
{
public:
   Program m_program;
   AttributeBinderVAO m_binder;

   EffectColored() :
      Effect(),
      m_program(),
      m_binder()
   {
   }

   bool init()
   {
     const char* vsh_source =
       "attribute vec3 a_vertex;                     \n"
       "attribute vec3 a_color;                      \n"
       "varying vec3 v_color;                        \n"
       "uniform mat4 u_mvp;                          \n"
       "                                             \n"
       "void main()                                  \n"
       "{                                            \n"
       "  v_color = a_color;                         \n"
       "  gl_Position = u_mvp * vec4(a_vertex, 1.0); \n"
       "}                                            \n";
  
     const char* fsh_source =
       "varying vec3 v_color;                \n"
       "                                     \n"
       "void main()                          \n"
       "{                                    \n"
       "  gl_FragColor = vec4(v_color, 1.0); \n"
       "}                                    \n";
  
     Shader vsh(GL_VERTEX_SHADER);
     if (vsh.isInited() && vsh.load(vsh_source))
     {
       Shader fsh(GL_FRAGMENT_SHADER);
       if (fsh.isInited() && fsh.load(fsh_source))
       {
         if (m_program.attach(vsh) && m_program.attach(fsh) && m_program.link())
         {
           
           
           
           
           return true;
         }
       }
     }
     return false;
   }

   virtual void draw(DrawContext& context, Geometry& geometry, Material& material) override
   {
      m_program.use();
      
      const Program::index_t vertices_loc = m_program.findAttributeLocation("a_vertex");
      geometry.setAttributeLocation(Geometry::VERTEX, vertices_loc);

      const Program::index_t colors_loc = m_program.findAttributeLocation("a_color");
      geometry.setAttributeLocation(Geometry::COLOR, colors_loc);

      geometry.bindAttributes();
      
      //m_binder.bind();

      Matrix4f m;
      geometry.m_transform.genMatrix(m);

      Matrix4f res_m;
      dot(res_m, context.m_model_view, m);
      
      const Program::index_t mvp_loc = m_program.findUniformLocation("u_mvp");
      //glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, context.m_model_view.buffer());
      glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, res_m.buffer());

      geometry.drawCall();
   }
};

class DrawManager
{
public:
   class Item
   {
   public:
      Geometry* m_geometry;
      Material* m_material;
   };

   std::vector<Item> m_items;

   Item* createItem()
   {
      m_items.push_back(Item());
      return &m_items.back();
   }

   virtual void draw(DrawContext& context)
   {
      for (auto item : m_items)
      {
         auto geometry = item.m_geometry;
         auto material = item.m_material;
         if (geometry != nullptr && material != nullptr)
         {
            auto effect = material->m_effect;
            if (effect != nullptr)
            {
               effect->draw(context, *geometry, *material);
            }
         }
      }
   }
};

class Entity
{
public:

};

class SceneManager
{
public:
   std::vector<Entity> m_entities;

   Entity* createEntity()
   {
      m_entities.push_back(Entity());
      return &m_entities.back();
   }

};


class MyDrawHandler : public DrawHandler
{
public:
  MyDrawHandler(DrawManager& draw_manager, DrawContext& context, const Matrix4f& proj) :
    DrawHandler(),
    m_draw_manager(draw_manager),
    m_context(context),
    m_proj(proj)
  {
  }
  
  virtual void draw()
  {
    //uint64_t delta_time = 


    static float phi_1 = 0.0f;
    if ((phi_1 += 0.01f) >= 6.28f)
    {
      phi_1 -= 6.28f;
    }
    Transform3f trans;
    //trans.setIdentity();
    //trans.setScale(Vector3f(0.2f));
    trans.setTranslate(Vector3f(0.0f, 0.0f, 150.0f));
    trans.rotateX(-3.14f / 6);
    trans.rotateY(phi_1);
    
    Matrix4f mv;
    trans.genMatrix(mv);

    Matrix4f mvp;
    dot(mvp, m_proj, mv);
    
    /*float vertices[8 * 3] = 
    {
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f
    };
    dada::uint8_t colors[8 * 3] =
    {
      255,   0,   0,
        0, 255,   0,
        0,   0, 255,
        0,   0,   0,
      255, 255,   0,
      255, 255, 255,
        0, 255, 255,
      255,   0, 255
    };
    unsigned char indices[19] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1,   1, 7, 3, 5,   5,   6, 4, 0, 2 };*/
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);

    m_context.m_model_view = mvp;
    
    m_draw_manager.draw(m_context);
  }

private:
   DrawManager& m_draw_manager;
   DrawContext& m_context;
  const Matrix4f& m_proj;
};

class MyResizeHandler : public ResizeHandler
{
public:
  MyResizeHandler(Matrix4f& proj) :
    ResizeHandler(),
    m_proj(proj)
  {
  }

  virtual void resize(dada::uint16_t width, dada::uint16_t height)
  {
    glViewport(0, 0, width, height);
    if (width > height)
    {
      if (height == 0)
      {
        height = 1;
      }
      const float aspect = (float)width / (float)height;
      //Transform3f::genOrtho(m_proj, -aspect, aspect, -1.0f, 1.0f, -3.0f, -1.0f);
      //Transform3f::genFrustum(m_proj, -aspect, aspect, -1.0f, 1.0f, 1.0f, 3.0f);
      Transform3f::genPerspective(m_proj, 3.14f / 2.0f, aspect, 1.0f, 300.0f);
    }
    else
    {
      if (width == 0)
      {
        width = 1;
      }
      const float aspect = (float)height / (float)width;
      //genOrtho(m_proj, -1.0f, 1.0f, -aspect, aspect, -1.0f, 1.0f);
      //Transform3f::genOrtho(m_proj, -1.0f, 1.0f, -aspect, aspect, -3.0f, -1.0f);
      //Transform3f::genFrustum(m_proj, -1.0f, 1.0f, -aspect, aspect, 1.0f, 3.0f);
      Transform3f::genPerspective(m_proj, 3.14f / 2.0f, 1.0f / aspect, 1.0f, 300.0f);
    }
  }

private:
  Matrix4f& m_proj;
};

int main(int argc, char* argv[])
{
  Matrix4f proj(1.0f);

  Application app;

  MyResizeHandler resize_handler(proj);
  app.setResizeHandler(&resize_handler);
  
  WindowInfo wi;
  if (app.createWindow(wi))
  {
    EffectColored effect;
    effect.init();

    Material material;
    material.m_effect = &effect;
    
    

    GeometryBoxColorIndirect* geometries = new GeometryBoxColorIndirect[10000];
    //GeometryBoxColorVBO geometry;
    //GeometryBoxColorVAO geometry[10000];

    DrawManager draw_manager;
    DrawContext draw_context;
    
    for (int i = 0; i < 100; i++)
    {
      for (int j = 0; j < 100; j++)
      {
         const int n = i * 100 + j;

         DrawManager::Item* draw_item = draw_manager.createItem();
         draw_item->m_geometry = geometries + n;
         draw_item->m_material = &material;
         draw_item->m_geometry->m_transform.translate(Vector3f(-10.0f + i * 2.0f, -10.0f + j * 2.0f, 0.0f));
      }
    }
    
    
    
    MyDrawHandler draw_handler(draw_manager, draw_context, proj);
    app.setDrawHandler(&draw_handler);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    app.run();

    delete geometries;
  }

  return 0;
}
