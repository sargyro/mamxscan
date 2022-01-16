import yaml
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams

# Global plot settings
plotCONTUR = False
shading = True
rcParams['hatch.linewidth'] = 0.2
#rcParams["mathtext.fontset"] = "cm"
MAJOR_TICK_LENGTH = 6
MINOR_TICK_LENGTH = 3
ALPHA=0.2

def expFun(x, a, b, c):
    return a * np.exp(-b * x) + c

class Plot:
    def __init__(self, x, y, titleX, titleY, rangeX, rangeY, legend):
        self.x = x
        self.y = y
        self.titleX = titleX
        self.titleY = titleY
        self.rangeX = rangeX
        self.rangeY = rangeY
        self.legend = legend

def getXYfromYAML(inputFile):
    f = open(inputFile)
    parsed = yaml.load(f, Loader=yaml.FullLoader)
    # Get X variable
    y = parsed.get('dependent_variables')[0].get('values')
    x = parsed.get('independent_variables')[0].get('values')
    x_list = [float(i.get('value')) for i in x]
    y_list = [float(i.get('value')) for i in y]
    return np.asarray(x_list), np.asarray(y_list)

def plot(Plots):
    loop=1
    for p in Plots:
        # Line format
        fmt="-"
        col=""
        if "mono" in p.legend: col='g'
        elif "4b" in p.legend: col='r'
        elif "2b" in p.legend: col='b'
        elif "Omega" in p.legend: col='grey'
        # Plot
        linewidth=2.5 if "Omega" not in p.legend else 0.5
        label=p.legend if "island" not in p.legend else None
        plt.plot(p.x, p.y, fmt, color=col, label=label, linewidth=linewidth)
        if "Omega" not in p.legend:
          plt.gca().fill_betweenx(p.y, p.x, color=col, alpha=ALPHA)
        else:
           rcParams['hatch.linewidth'] = 0.8
           if "island" in p.legend:
             plt.fill(p.x, p.y, alpha=0.8, edgecolor=col, facecolor="None", hatch="\ "*3)
           else:
             plt.gca().fill_between(p.x, p.y, alpha=ALPHA, edgecolor=col, facecolor="None", hatch="\ "*3)
   
    # Add diagonal
    line_x = np.arange(0, 550, 50)
    line_y = [0.5*i for i in line_x]
    plt.plot(line_x, line_y, '-.', color='grey', linewidth=0.6)
    plt.text(440, 230, r"$m_{\chi}=m_{a}/2$", rotation=20, fontsize='small', color='gray')
    
    # Plot cosmetics
    plt.title(r"$m_{A}=1200$ GeV, $\sin\theta=0.35$, $\tan\beta=1$, $\lambda_{3,P_1,P_2}=3$", fontsize=15)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    plt.xlabel(Plots[0].titleX, fontsize=15)
    plt.ylabel(Plots[0].titleY, fontsize=15)
    plt.xlim([Plots[0].rangeX[0], p.rangeX[1]])
    plt.ylim([Plots[0].rangeY[0], p.rangeY[1]])
    # Change how the tick marks are printed
    axes = plt.gca()
    axes.tick_params("both", which="both", direction="in")
    axes.tick_params("both", which="major", length=MAJOR_TICK_LENGTH)
    axes.tick_params("both", which="minor", length=MINOR_TICK_LENGTH)
    axes.tick_params("x", which="both", top=True)
    axes.tick_params("y", which="both", right=True)
    plt.legend(loc='best', handlelength=2.5, prop={'size': 8.5})
    plt.savefig(f'excl.pdf', bbox_inches="tight")
    plt.close()
    rcParams['hatch.linewidth'] = 0.2


###

x,y = getXYfromYAML("monoHbb.yaml")
monoH = Plot(x,y,r"$m_a$ [GeV]",r"$m_{\chi}$ [GeV]",[0,500],[10,490],r"ATLAS mono-$h(b\bar{b})$, 139 fb$^{-1}$")

x,y = getXYfromYAML("4b.yaml")
bbbb = Plot(x,y,r"$m_a$ [GeV]",r"$m_{\chi}$ [GeV]",[0,500],[10,490],r"ATLAS $4b$, 36 fb$^{-1}$")

x,y = getXYfromYAML("2b2m.yaml")
bbmm = Plot(x,y,r"$m_a$ [GeV]",r"$m_{\chi}$ [GeV]",[0,500],[10,490],r"ATLAS $2b2\mu$, 139 fb$^{-1}$")

x,y = getXYfromYAML("2b2m.yaml")
bbmm = Plot(x,y,r"$m_a$ [GeV]",r"$m_{\chi}$ [GeV]",[0,500],[10,490],r"ATLAS $2b2\mu$, 139 fb$^{-1}$")

x,y = getXYfromYAML("RDmain.yaml")
RDmain = Plot(x,y,r"$m_a$ [GeV]",r"$m_{\chi}$ [GeV]",[0,500],[10,490],r"$\Omega_{\mathrm{DM}} h^2 > 0.12$")

x,y = getXYfromYAML("RDisland.yaml")
RDisland = Plot(x,y,r"$m_a$ [GeV]",r"$m_{\chi}$ [GeV]",[0,500],[10,490],r"$\Omega_{\mathrm{DM}} h^2 > 0.12$ island")

plot([monoH, bbbb, bbmm, RDmain, RDisland])
