#ifndef WTRACKMENU_H
#define WTRACKMENU_H

#include <QAction>
#include <QMenu>
#include <QWidget>

#include "control/controlproxy.h"
#include "library/dao/playlistdao.h"
#include "library/dlgtagfetcher.h"
#include "library/dlgtrackinfo.h"
#include "library/trackcollectionmanager.h"
#include "library/trackmodel.h"
#include "preferences/usersettings.h"
#include "widget/wcolorpickeraction.h"
#include "widget/wcoverartmenu.h"

typedef QList<TrackId> TrackIdList;
typedef QList<TrackPointer> TrackPointerList;

class WTrackMenu : public QMenu {
    Q_OBJECT
  public:
    enum Filter {
        None = 0,
        AutoDJ = 1,
        LoadTo = 1 << 1,
        Playlist = 1 << 2,
        Crate = 1 << 3,
        Remove = 1 << 4,
        Metadata = 1 << 5,
        Reset = 1 << 6,
        BPM = 1 << 7,
        Color = 1 << 8,
        HideUnhidePurge = 1 << 9,
        FileBrowser = 1 << 10,
        Properties = 1 << 11,
    };
    Q_DECLARE_FLAGS(Filters, Filter)

    WTrackMenu(QWidget *parent, UserSettingsPointer pConfig, TrackCollectionManager* pTrackCollectionManager, Filters flags = Filter::None);
    ~WTrackMenu() {}

    void setTrackId(TrackId track);
    void setTrackIds(TrackIdList trackList);
    void setTrackIndexList(QModelIndexList indexList);
    void setTrackModel(TrackModel* trackModel);

  private slots:
    // File
    void slotOpenInFileBrowser();
    
    // Row color
    void slotColorPicked(mixxx::RgbColor::optional_t color);

    // Reset
    void slotClearBeats();
    void slotClearPlayCount();
    void slotClearMainCue();
    void slotClearHotCues();
    void slotClearIntroCue();
    void slotClearOutroCue();
    void slotClearLoop();
    void slotClearKey();
    void slotClearReplayGain();
    void slotClearWaveform();
    void slotClearAllMetadata();

    // BPM
    void slotLockBpm();
    void slotUnlockBpm();
    void slotScaleBpm(int);
    
    // Info and metadata
    void slotNextTrackInfo();
    void slotNextDlgTagFetcher();
    void slotPrevTrackInfo();
    void slotPrevDlgTagFetcher();
    void slotShowTrackInTagFetcher(TrackPointer track);
    void slotTrackInfoClosed();
    void slotTagFetcherClosed();
    void slotShowTrackInfo();
    void slotShowDlgTagFetcher();
    void slotImportTrackMetadataFromFileTags();
    void slotExportTrackMetadataIntoFileTags();
    void slotUpdateExternalTrackCollection(ExternalTrackCollection *externalTrackCollection);

    // Playlist and crate
    void slotPopulatePlaylistMenu();
    void slotPopulateCrateMenu();
    void addSelectionToNewCrate();

    // Auto DJ
    void slotAddToAutoDJBottom();
    void slotAddToAutoDJTop();
    void slotAddToAutoDJReplace();

    // Cover
    void slotCoverInfoSelected(const CoverInfoRelative &coverInfo);
    void slotReloadCoverArt();

    // Library management
    void slotRemove();
    void slotHide();
    void slotUnhide();
    void slotPurge();
    
public:
    signals:
    void loadTrackToPlayer(TrackPointer pTrack, QString group,
            bool play = false);

private:
    void teardownActions();
    void constructMenus();
    void createActions();
    void setupActions();

    bool modelHasCapabilities(TrackModel::CapabilitiesFlags capabilities) const;
    bool optionIsEnabled(Filter flag) const;

    void addSelectionToPlaylist(int iPlaylistId);
    void updateSelectionCrates(QWidget* pWidget);

    void showTrackInfo(QModelIndex index);
    void showDlgTagFetcher(QModelIndex index);

    void addToAutoDJ(PlaylistDAO::AutoDJSendLoc loc);

    void lockBpm(bool lock);

    void loadSelectionToGroup(QString group, bool play = false);
    void clearTrackSelection();

    // Selected tracks
    TrackIdList m_pTrackIdList;
    TrackPointerList m_pTrackPointerList;
    QModelIndexList m_pSelectedTrackIndices;

    TrackModel* m_pTrackModel{};

    ControlProxy* m_pNumSamplers{};
    ControlProxy* m_pNumDecks{};
    ControlProxy* m_pNumPreviewDecks{};

    // Submenus
    QMenu *m_pLoadToMenu{};
    QMenu *m_pDeckMenu{};
    QMenu *m_pSamplerMenu{};
    QMenu *m_pPlaylistMenu{};
    QMenu *m_pCrateMenu{};
    QMenu *m_pMetadataMenu{};
    QMenu *m_pMetadataUpdateExternalCollectionsMenu{};
    QMenu *m_pClearMetadataMenu{};
    QMenu *m_pBPMMenu{};
    QMenu *m_pColorMenu{};
    WCoverArtMenu* m_pCoverMenu{};

    // Reload Track Metadata Action:
    QAction *m_pImportMetadataFromFileAct{};
    QAction *m_pImportMetadataFromMusicBrainzAct{};

    // Save Track Metadata Action:
    QAction *m_pExportMetadataAct{};

    // Load Track to PreviewDeck
    QAction* m_pAddToPreviewDeck{};

    // Send to Auto-DJ Action
    QAction *m_pAutoDJBottomAct{};
    QAction *m_pAutoDJTopAct{};
    QAction *m_pAutoDJReplaceAct{};

    // Remove from table
    QAction *m_pRemoveAct{};
    QAction *m_pRemovePlaylistAct{};
    QAction *m_pRemoveCrateAct{};
    QAction *m_pHideAct{};
    QAction *m_pUnhideAct{};
    QAction *m_pPurgeAct{};

    // Show track-editor action
    QAction *m_pPropertiesAct{};
    
    // Open file in default file browser
    QAction *m_pFileBrowserAct{};

    // BPM feature
    QAction *m_pBpmLockAction{};
    QAction *m_pBpmUnlockAction{};
    QAction *m_pBpmDoubleAction{};
    QAction *m_pBpmHalveAction{};
    QAction *m_pBpmTwoThirdsAction{};
    QAction *m_pBpmThreeFourthsAction{};
    QAction *m_pBpmFourThirdsAction{};
    QAction *m_pBpmThreeHalvesAction{};

    // Track color
    WColorPickerAction *m_pColorPickerAction{};

    // Clear track metadata actions
    QAction* m_pClearBeatsAction{};
    QAction* m_pClearPlayCountAction{};
    QAction* m_pClearMainCueAction{};
    QAction* m_pClearHotCuesAction{};
    QAction* m_pClearIntroCueAction{};
    QAction* m_pClearOutroCueAction{};
    QAction* m_pClearLoopAction{};
    QAction* m_pClearWaveformAction{};
    QAction* m_pClearKeyAction{};
    QAction* m_pClearReplayGainAction{};
    QAction* m_pClearAllMetadataAction{};

    const UserSettingsPointer m_pConfig;
    TrackCollectionManager* m_pTrackCollectionManager;

    QScopedPointer<DlgTrackInfo> m_pTrackInfo;
    QScopedPointer<DlgTagFetcher> m_pTagFetcher;

    QModelIndex currentTrackInfoIndex;

    struct UpdateExternalTrackCollection {
        QPointer<ExternalTrackCollection> externalTrackCollection;
        QAction* action{};
    };
    QList<UpdateExternalTrackCollection> m_updateInExternalTrackCollections;
    
    bool m_bPlaylistMenuLoaded;
    bool m_bCrateMenuLoaded;

    // Column numbers
    int m_iCoverSourceColumn; // cover art source
    int m_iCoverTypeColumn; // cover art type
    int m_iCoverLocationColumn; // cover art location
    int m_iCoverHashColumn; // cover art hash
    int m_iCoverColumn; // visible cover art
    int m_iTrackLocationColumn;

    // Filter available options
    Filters m_eFilters;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(WTrackMenu::Filters)


#endif // WTRACKMENU_H
