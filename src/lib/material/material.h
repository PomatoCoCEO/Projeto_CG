#include <GL/glut.h>
struct material
{
    // GLfloat rAmbient, gAmbient, bAmbient;
    GLfloat amb[4], diff[4], spec[4];
    // GLfloat rDiffuse, gDiffuse, bDiffuse;
    // GLfloat rSpec, gSpec, bSpec;
    GLfloat shininess, alpha = 1.0;
    material(GLfloat rAmbient, GLfloat gAmbient, GLfloat bAmbient,
             GLfloat rDiffuse, GLfloat gDiffuse, GLfloat bDiffuse,
             GLfloat rSpec, GLfloat gSpec, GLfloat bSpec, GLfloat shininess = 1.0, GLfloat alpha = 1.0) : shininess(shininess), alpha(alpha)
    {
        amb[0] = rAmbient, amb[1] = gAmbient, amb[2] = bAmbient, amb[3] = alpha;
        diff[0] = rDiffuse, diff[1] = gDiffuse, diff[2] = bDiffuse, diff[3] = alpha;
        spec[0] = rSpec, spec[1] = gSpec, spec[2] = bSpec, spec[3] = alpha;
    }
    material() {}
    void apply()
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
        glMaterialf(GL_FRONT, GL_SHININESS, (GLfloat)shininess * 128.0);
    }
};

/*0*/ const material WHITE_MAT = material(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
/*1*/ const material EMERALD = material(0.0215, 0.1745, 0.0215, 0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6, 1);
/*2*/ const material JADE = material(0.135, 0.2225, 0.1575, 0.54, 0.89, 0.63, 0.316228, 0.316228, 0.316228, 0.1, 1);
/*3*/ const material OBSIDIAN = material(0.05375, 0.05, 0.06625, 0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.3, 1);
/*4*/ const material PEARL = material(0.25, 0.20725, 0.20725, 1, 0.829, 0.829, 0.296648, 0.296648, 0.296648, 0.088, 1);
/*5*/ const material RUBY = material(0.1745, 0.01175, 0.01175, 0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6, 0.5);
/*6*/ const material TURQUOISE = material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1, 1);
/*7*/ const material BRASS = material(0.329412, 0.223529, 0.027451, 0.780392, 0.568627, 0.113725, 0.992157, 0.941176, 0.807843, 0.217949, 1);
/*8*/ const material BRONZE = material(0.2125, 0.1275, 0.054, 0.714, 0.4284, 0.18144, 0.393548, 0.271906, 0.166721, 0.2, 1);
/*9*/ const material CHROME = material(0.25, 0.25, 0.25, 0.4, 0.4, 0.4, 0.774597, 0.774597, 0.774597, 0.6, 1);
/*10*/ const material COPPER = material(0.19125, 0.0735, 0.0225, 0.7038, 0.27048, 0.0828, 0.256777, 0.137622, 0.086014, 0.1, 1);
/*11*/ const material GOLD = material(0.24725, 0.1995, 0.0745, 0.75164, 0.60648, 0.22648, 0.628281, 0.555802, 0.366065, 0.4, 1);
/*12*/ const material SILVER = material(0.19225, 0.19225, 0.19225, 0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4, 1);
/*13*/ const material BLACK_PLASTIC = material(0, 0, 0, 0.01, 0.01, 0.01, 0.5, 0.5, 0.5, 0.25, 1);
/*14*/ const material CYAN_PLASTIC = material(0, 0.1, 0.06, 0, 0.509804, 0.509804, 0.501961, 0.501961, 0.501961, 0.25, 1);
/*15*/ const material GREEN_PLASTIC = material(0, 0, 0, 0.1, 0.35, 0.1, 0.45, 0.55, 0.45, 0.25, 1);
/*16*/ const material RED_PLASTIC = material(0, 0, 0, 0.5, 0, 0, 0.7, 0.6, 0.6, 0.25, 1);
/*17*/ const material WHITE_PLASTIC = material(0, 0, 0, 0.55, 0.55, 0.55, 0.7, 0.7, 0.7, 0.25, 1);
/*18*/ const material YELLOW_PLASTIC = material(0, 0, 0, 0.5, 0.5, 0, 0.6, 0.6, 0.5, 0.25, 1);
/*19*/ const material BLACK_RUBBER = material(0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.4, 0.4, 0.4, 0.078125, 1);
/*20*/ const material CYAN_RUBBER = material(0, 0.05, 0.05, 0.4, 0.5, 0.5, 0.04, 0.7, 0.7, 0.078125, 1);
/*21*/ const material GREEN_RUBBER = material(0, 0.05, 0, 0.4, 0.5, 0.4, 0.04, 0.7, 0.04, 0.078125, 1);
/*22*/ const material RED_RUBBER = material(0.05, 0, 0, 0.5, 0.4, 0.4, 0.7, 0.04, 0.04, 0.078125, 1);
/*23*/ const material WHITE_RUBBER = material(0.05, 0.05, 0.05, 0.5, 0.5, 0.5, 0.7, 0.7, 0.7, 0.078125, 1);
/*24*/ const material YELLOW_RUBBER = material(0.05, 0.05, 0, 0.5, 0.5, 0.4, 0.7, 0.7, 0.04, 0.078125, 1);
/*25*/ const material LATEX = material(0.05, 0.05, 0, 0, 0, 0, 0.9, 0.9, 0.9, 1, 1);
/*26*/ const material WHITE_GLASS = material(0.5, 0.5, 0.5, 0.7, 0.7, 0.7, 0.8, 0.8, 0.8, 1, 0.5);
static material materials[] = {WHITE_MAT, EMERALD, JADE, OBSIDIAN, PEARL, RUBY, TURQUOISE, BRASS,                                                     // 7
                               BRONZE, CHROME, COPPER, GOLD, SILVER, BLACK_PLASTIC, CYAN_PLASTIC, GREEN_PLASTIC, RED_PLASTIC, WHITE_PLASTIC,          /// 17
                               YELLOW_PLASTIC, BLACK_RUBBER, CYAN_RUBBER, GREEN_RUBBER, RED_RUBBER, WHITE_RUBBER, YELLOW_RUBBER, LATEX, WHITE_GLASS}; // 24