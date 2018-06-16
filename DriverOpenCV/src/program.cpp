/*=============================================================================
Copyright (C) 2013 Allied Vision Technologies.  All Rights Reserved.

Redistribution of this file, in original or modified form, without
prior written consent of Allied Vision Technologies is prohibited.

-------------------------------------------------------------------------------

File:        program.cpp

Description: Implementation of main entry point of AsynchronousGrabConsole
   example of VimbaCPP.

-------------------------------------------------------------------------------

THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF TITLE,
NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR  PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#include <string>
#include <cstring>
#include <iostream>

#include "ThreadPool.h"

#include "VimbaCPP/Include/VimbaCPP.h"
#include "ApiController.h"

int main( int argc, char* argv[] )
{
if(argc < 2)
{
std::cout << "Please input camera name in command line!!!\n";
std::cout << "./ExeProgName <camera_name1> <camera_name2>" <<std::endl;
}



std::cout<<"///////////////////////////////////////////\n";
std::cout<<"/// Vimba API Asynchronous Grab Example ///\n";
std::cout<<"///////////////////////////////////////////\n\n";

//////////////////////
//Parse command line//
//////////////////////
/*AVT::VmbAPI::Examples::ProgramConfig Config;
err = Config.ParseCommandline( argc, argv);
//Write out an error if we could not parse the command line
if ( VmbErrorBadParameter == err )
{
std::cout<< "Invalid parameters!\n\n" ;
Config.setPrintHelp( true );
}

//Print out help and end program
if ( Config.getPrintHelp() )
{
Config.PrintHelp( std::cout );
}*/
//else
ThreadPool pool(argc);
std::vector< std::future<int> > results;
for(int i = 1; i < argc; ++i) {
    results.emplace_back(
            pool.enqueue([i, argv] {
                VmbErrorType err = VmbErrorSuccess;
                AVT::VmbAPI::Examples::ApiController apiController;

                // Print out version of Vimba
                std::cout << "Vimba Version V" << apiController.GetVersion() << "\n";
                // Startup Vimba
                err = apiController.StartUp();
                if (VmbErrorSuccess == err) {
                    AVT::VmbAPI::Examples::ProgramConfig Config;
                    if (Config.getCameraID().empty()) {
                        AVT::VmbAPI::CameraPtrVector cameras = apiController.GetCameraList();
                        if (cameras.empty()) {
                            err = VmbErrorNotFound;
                        } else {
                            std::string strCameraID;
                            strCameraID = std::string(argv[i]);
                            Config.setCameraID(strCameraID);
                        }
                    }
                    if (VmbErrorSuccess == err) {
                        std::cout << "Opening camera with ID: " << Config.getCameraID() << "\n";
                        err = apiController.StartContinuousImageAcquisition(Config);
                        if (VmbErrorSuccess == err) {
                            std::cout << "Press <enter> to stop aquision...\n";
                            getchar();
                            apiController.StopContinuousImageAcquisition();
                        }
                    }
                    apiController.ShutDown();
                }

                if (VmbErrorSuccess == err) {
                    std::cout << "\nAcquisition stopped.\n";
                } else {
                    std::string strError = apiController.ErrorCodeToMessage(err);
                    std::cout << "\nAn error occurred: " << strError << "\n";
                }
                return 0;
            })
    );
}
std::cout << "Quit main process ! \n";


}
