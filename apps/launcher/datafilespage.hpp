#ifndef DATAFILESPAGE_H
#define DATAFILESPAGE_H

#include <QWidget>
#include <QModelIndex>

class QTableView;
class QSortFilterProxyModel;
class QAction;
class QToolBar;
class QSplitter;
class QMenu;

class ProfilesComboBox;
class DataFilesModel;

class TextInputDialog;
class ProfilesComboBox;
class GameSettings;
class LauncherSettings;

namespace Files { struct ConfigurationManager; }

class DataFilesPage : public QWidget
{
    Q_OBJECT

public:
    DataFilesPage(Files::ConfigurationManager &cfg, GameSettings &gameSettings, LauncherSettings &launcherSettings, QWidget *parent = 0);

    ProfilesComboBox *mProfilesComboBox;

    void writeConfig(QString profile = QString());
    void saveSettings();


public slots:
    void setCheckState(QModelIndex index);

    void filterChanged(const QString filter);
    void showContextMenu(const QPoint &point);
    void profileChanged(const QString &previous, const QString &current);
    void profileRenamed(const QString &previous, const QString &current);
    void updateOkButton(const QString &text);
    void updateSplitter();

    // Action slots
    void newProfile();
    void deleteProfile();
//    void moveUp();
//    void moveDown();
//    void moveTop();
//    void moveBottom();
    void check();
    void uncheck();
    void refresh();

private:
    DataFilesModel *mMastersModel;
    DataFilesModel *mPluginsModel;

    QSortFilterProxyModel *mPluginsProxyModel;

    QTableView *mMastersTable;
    QTableView *mPluginsTable;

    QToolBar *mProfileToolBar;
    QMenu *mContextMenu;
    QSplitter *mSplitter;

    QAction *mNewProfileAction;
    QAction *mDeleteProfileAction;

//    QAction *mMoveUpAction;
//    QAction *mMoveDownAction;
//    QAction *mMoveTopAction;
//    QAction *mMoveBottomAction;
    QAction *mCheckAction;
    QAction *mUncheckAction;

    Files::ConfigurationManager &mCfgMgr;

    GameSettings &mGameSettings;
    LauncherSettings &mLauncherSettings;

    TextInputDialog *mNewProfileDialog;

//    const QStringList checkedPlugins();
//    const QStringList selectedMasters();

    void createActions();
    void setupDataFiles();
    void setupConfig();
    void readConfig();

    void loadSettings();

};

#endif
