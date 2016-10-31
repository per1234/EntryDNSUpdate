/*
  EntryDNSUpdate.h - Library for updating dynamic DNS entry at entrydns.net
  Created by Kristian Berg, October 24, 2016.
  Released into the public domain.
*/

#ifndef EntryDNSUpdate_h
#define EntryDNSUpdate_h

#endif

class EntryDNSUpdate {
  public:
    EntryDNSUpdate(String _token, unsigned long _updateFrequencySeconds = 300);
    void update();
  private:
    void doUpdate();
    const char *host = "entrydns.net";
    const int httpsPort = 443;
    const unsigned long updateFrequencySeconds; 

    // Use web browser to view and copy
    // SHA1 fingerprint of the certificate
    const char *fingerprint = "50 5a d6 fb 4c 86 b1 0b e4 68 54 1d 4e 73 5f 3e 3e 1a 4f ec";
    // Token for your host. You find this in your account in EntryDNS
    const String token;
    // The time when doUpdate was last performed
    unsigned long lastUpdated = 0;
};

