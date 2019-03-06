// This file is part of Dust Racing 2D.
// Copyright (C) 2012 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "difficultyprofile.hpp"
#include "inputhandler.hpp"

#include <map>
#include <QString>

class Track;

//! Singleton settings class that wraps the use of QSettings.
class Settings
{
public:

    //! Constructor.
    Settings();

    static Settings & instance();

    void saveLapRecord(const Track & track, int msecs);
    int loadLapRecord(const Track & track) const;
    void resetLapRecords();

    void saveRaceRecord(const Track & track, int msecs, int lapCount, DifficultyProfile::Difficulty difficulty);
    int loadRaceRecord(const Track & track, int lapCount, DifficultyProfile::Difficulty difficulty) const;
    void resetRaceRecords();

    void saveBestPos(const Track & track, int pos, int lapCount, DifficultyProfile::Difficulty difficulty);
    int loadBestPos(const Track & track, int lapCount, DifficultyProfile::Difficulty difficulty) const;
    void resetBestPos();

    void saveTrackUnlockStatus(const Track & track, int lapCount, DifficultyProfile::Difficulty difficulty);
    bool loadTrackUnlockStatus(const Track & track, int lapCount, DifficultyProfile::Difficulty difficulty) const;
    void resetTrackUnlockStatuses();

    void saveResolution(int hRes, int vRes, bool fullScreen);
    void loadResolution(int & hRes, int & vRes, bool & fullScreen);
    void getResolution(int & hRes, int & vRes, bool & fullScreen);

    void saveKeyMapping(int player, InputHandler::Action action, int key);
    int loadKeyMapping(int player, InputHandler::Action action);

    void saveDifficulty(DifficultyProfile::Difficulty difficulty);
    DifficultyProfile::Difficulty loadDifficulty() const;

    void saveVSync(int value);
    int loadVSync();

    void saveValue(QString key, int value);
    int loadValue(QString key, int defaultValue = 0);

    static QString difficultyKey();

    static QString fpsKey();

    static QString lapCountKey();

    static QString soundsKey();

    static QString screenKey();

    static QString vsyncKey();

    int getLapCount();
    void setLapCount(int lapCount);
    void saveLapCount(int lapCount);
    void resetLapCount();

public:
    void setMenusDisabled(bool menusDisabled) {
    	m_menusDisabled = menusDisabled;
    }

    bool getMenusDisabled() const {
    	return m_menusDisabled;
    }

    void setGameMode(const QString& gameMode) {
    	m_gameMode = gameMode;
    }

    const QString& getGameMode() const {
    	return m_gameMode;
    }

    const QString& getCustomTrackFile() const {
    	return m_customTrackFile;
    }

    void setCustomTrackFile(const QString& customTrackFile) {
    	m_customTrackFile = customTrackFile;
    }

    //! Sets the resolution as specified at command line.
    void setTermResolution(int hRes, int vRes, bool fullScreen) {
    	m_hRes = hRes;
    	m_vRes = vRes;
    	m_fullScreen = fullScreen;
    }

    void setUseTermResolution(bool useTermResolution) {
    	m_useTermResolution = useTermResolution;
    }

    bool getDisableRendering() const {
    	return m_disableRendering;
    }

    void setDisableRendering(bool disableRendering) {
    	m_disableRendering = disableRendering;
    	if(m_disableRendering) m_menusDisabled = true;
    }

    bool getResetStuckPlayer() const {
        return m_resetStuckPlayer;
    }

    void setResetStuckPlayer(bool resetStuckPlayer) {
        m_resetStuckPlayer = resetStuckPlayer;
    }

    float getCameraSmoothing() const {
        return m_cameraSmoothing;
    }

    void setCameraSmoothing(float cameraSmoothing) {
        m_cameraSmoothing = cameraSmoothing;
    }

private:
QString m_customTrackFile;
    bool m_menusDisabled;
    QString m_gameMode;
    int m_lapCount;
    bool m_lapCountSet = false;

    int m_hRes;
    int m_vRes;
    bool m_fullScreen;
    bool m_useTermResolution = false;

    bool m_disableRendering = false;
    bool m_resetStuckPlayer = false;

    float m_cameraSmoothing = 0.05;

    QString combineActionAndPlayer(int player, InputHandler::Action action);

    static Settings * m_instance;
    std::map<InputHandler::Action, QString> m_actionToStringMap;
};

#endif // SETTINGS_HPP
