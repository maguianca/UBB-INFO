package ro.mpp2025.controller;

import ro.mpp2025.Service.IAppService;

public class Controller {

    IAppService appService;

    public IAppService getAppService() {
        return appService;
    }

    public void setAppService(IAppService appService) {
        this.appService = appService;
    }

    public static void displayException(Exception e){
        Utils.showMessageBox(e.getMessage());
    }
}
